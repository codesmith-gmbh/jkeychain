/*
 * Copyright (c) 2011, Conor McDermottroe
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <Security/Security.h>

#include "pt_davidafsilva_apple_OSXKeychain.h"
#include <string.h>
#include <strings.h>

#define OSXKeychainException "pt/davidafsilva/apple/OSXKeychainException"

/* A simplified structure for dealing with jstring objects. Use jstring_unpack
 * and jstring_unpacked_free to manage these.
 */
typedef struct {
	int len;
	const char* str;
} jstring_unpacked;

/* Throw an exception.
 *
 * Parameters:
 *	env				The JNI environment.
 *	exceptionClass	The name of the exception class.
 *	message			The message to pass to the Exception.
 */
void throw_exception(JNIEnv* env, const char* exceptionClass, const char* message) {
	jclass cls = (*env)->FindClass(env, exceptionClass);
	/* if cls is NULL, an exception has already been thrown */
	if (cls != NULL) {
		(*env)->ThrowNew(env, cls, message);
	}
	/* free the local ref, utility funcs must delete local refs. */
	(*env)->DeleteLocalRef(env, cls);
}

/* Shorthand for throwing an OSXKeychainException from an OSStatus.
 *
 * Parameters:
 *	env		The JNI environment.
 *	status	The non-error status returned from a keychain call.
 */
void throw_osxkeychainexception(JNIEnv* env, OSStatus status) {
	CFStringRef errorMessage = SecCopyErrorMessageString(status, NULL);
	throw_exception(
		env,
		OSXKeychainException,
		CFStringGetCStringPtr(errorMessage, kCFStringEncodingMacRoman)
	);
	CFRelease(errorMessage);
}

/* Unpack the data from a jstring and put it in a jstring_unpacked.
 *
 * Parameters:
 *	env	The JNI environment.
 *	js	The jstring to unpack.
 *	ret	The jstring_unpacked in which to store the result.
 */
void jstring_unpack(JNIEnv* env, jstring js, jstring_unpacked* ret) {
	if (ret == NULL) {
		return;
	}
	if (env == NULL || js == NULL) {
		ret->len = 0;
		ret->str = NULL;
		return;
	}

	/* Get the length of the string. */
	ret->len = (int)((*env)->GetStringUTFLength(env, js));
	if (ret->len <= 0) {
		ret->len = 0;
		ret->str = NULL;
		return;
	}
	ret->str = (*env)->GetStringUTFChars(env, js, NULL);
}

/* Clean up a jstring_unpacked after it's no longer needed.
 *
 * Parameters:
 *	jsu	A jstring_unpacked structure to clean up.
 */
void jstring_unpacked_free(JNIEnv *env, jstring js, jstring_unpacked* jsu) {
	if (jsu != NULL && jsu->str != NULL) {
		(*env)->ReleaseStringUTFChars(env, js, jsu->str);
		jsu->len = 0;
		jsu->str = NULL;
	}
}

/* Implementation of OSXKeychain.addGenericPassword(). See the Java docs for
 * explanations of the parameters.
 */
JNIEXPORT void JNICALL Java_pt_davidafsilva_apple_OSXKeychain__1addGenericPassword(JNIEnv* env, jobject obj, jstring serviceName, jstring accountName, jstring password) {
	OSStatus status;
	jstring_unpacked service_name;
	jstring_unpacked account_name;
	jstring_unpacked service_password;

	/* Unpack the params */
	jstring_unpack(env, serviceName, &service_name);
	jstring_unpack(env, accountName, &account_name);
	jstring_unpack(env, password, &service_password);
	/* check for allocation failures */
	if (service_name.str == NULL || 
	    account_name.str == NULL || 
		service_password.str == NULL) {
		jstring_unpacked_free(env, serviceName, &service_name);
		jstring_unpacked_free(env, accountName, &account_name);
		jstring_unpacked_free(env, password, &service_password);
		return;
	}

	/* Add the details to the keychain. */
	status = SecKeychainAddGenericPassword(
		NULL,
		service_name.len,
		service_name.str,
		account_name.len,
		account_name.str,
		service_password.len,
		service_password.str,
		NULL
	);
	if (status != errSecSuccess) {
		throw_osxkeychainexception(env, status);
	}

	/* Clean up. */
	jstring_unpacked_free(env, serviceName, &service_name);
	jstring_unpacked_free(env, accountName, &account_name);
	jstring_unpacked_free(env, password, &service_password);
}

JNIEXPORT void JNICALL Java_pt_davidafsilva_apple_OSXKeychain__1modifyGenericPassword(JNIEnv *env, jobject obj, jstring serviceName, jstring accountName, jstring password) {
	OSStatus status;
	jstring_unpacked service_name;
	jstring_unpacked account_name;
	jstring_unpacked service_password;
	SecKeychainItemRef existingItem;

	/* Unpack the params */
	jstring_unpack(env, serviceName, &service_name);
	jstring_unpack(env, accountName, &account_name);
	jstring_unpack(env, password, &service_password);
	/* check for allocation failures */
	if (service_name.str == NULL || 
	    account_name.str == NULL || 
		service_password.str == NULL) {
		jstring_unpacked_free(env, serviceName, &service_name);
		jstring_unpacked_free(env, accountName, &account_name);
		jstring_unpacked_free(env, password, &service_password);
		return;
	}

	status = SecKeychainFindGenericPassword(
		NULL,
		service_name.len,
		service_name.str,
		account_name.len,
		account_name.str,
		NULL,
		NULL,
		&existingItem
	);
	if (status == errSecItemNotFound) {
	   /* add new key */
	   status = SecKeychainAddGenericPassword(
       		NULL,
       		service_name.len,
       		service_name.str,
       		account_name.len,
       		account_name.str,
       		service_password.len,
       		service_password.str,
       		NULL
       	);
       	if (status != errSecSuccess) {
            throw_osxkeychainexception(env, status);
        }
	}
	else if (status != errSecSuccess) {
		throw_osxkeychainexception(env, status);
	}
	else {
		/* Update the details in the keychain. */
		status = SecKeychainItemModifyContent(
			existingItem,
			NULL,
			service_password.len,
			service_password.str
		);
		if (status != errSecSuccess) {
			throw_osxkeychainexception(env, status);
		}
	}

	/* Clean up. */
	jstring_unpacked_free(env, serviceName, &service_name);
	jstring_unpacked_free(env, accountName, &account_name);
	jstring_unpacked_free(env, password, &service_password);
}

/* Implementation of OSXKeychain.findGenericPassword(). See the Java docs for
 * explanations of the parameters.
 */
JNIEXPORT jstring JNICALL Java_pt_davidafsilva_apple_OSXKeychain__1findGenericPassword(JNIEnv* env, jobject obj, jstring serviceName, jstring accountName) {
	OSStatus status;
	jstring_unpacked service_name;
	jstring_unpacked account_name;
	jstring result = NULL;

	/* Buffer for the return from SecKeychainFindGenericPassword. */
	void* password;
	UInt32 password_length;

	/* Query the keychain. */
	status = SecKeychainSetPreferenceDomain(kSecPreferencesDomainUser);
	if (status != errSecSuccess) {
		throw_osxkeychainexception(env, status);
		return NULL;
	}

	/* Unpack the params. */
	jstring_unpack(env, serviceName, &service_name);
	jstring_unpack(env, accountName, &account_name);
	if (service_name.str == NULL || 
	    account_name.str == NULL) {
		jstring_unpacked_free(env, serviceName, &service_name);
		jstring_unpacked_free(env, accountName, &account_name);
		return NULL;
	}
	
	status = SecKeychainFindGenericPassword(
		NULL,
		service_name.len,
		service_name.str,
		account_name.len,
		account_name.str,
		&password_length,
		&password,
		NULL
	);
	if (status == errSecItemNotFound) {
	    return NULL;
	}
	else if (status != errSecSuccess) {
		throw_osxkeychainexception(env, status);
	}
	else {
		// the returned value from keychain is not 
		// null terminated, so a copy is created. 
		char *password_buffer = malloc(password_length+1);
		memcpy(password_buffer, password, password_length);
		password_buffer[password_length] = 0;

		/* Create the return value. */
		result = (*env)->NewStringUTF(env, password_buffer);

		/* Clean up. */
		bzero(password_buffer, password_length);
		free(password_buffer);
		SecKeychainItemFreeContent(NULL, password);
	}
	jstring_unpacked_free(env, serviceName, &service_name);
	jstring_unpacked_free(env, accountName, &account_name);

	return result;
}

/* Implementation of OSXKeychain.deleteGenericPassword(). See the Java docs for
 * explanations of the parameters.
 */
JNIEXPORT void JNICALL Java_pt_davidafsilva_apple_OSXKeychain__1deleteGenericPassword(JNIEnv* env, jobject obj, jstring serviceName, jstring accountName) {
	OSStatus status;
	jstring_unpacked service_name;
	jstring_unpacked account_name;
	SecKeychainItemRef itemToDelete;

	/* Query the keychain. */
	status = SecKeychainSetPreferenceDomain(kSecPreferencesDomainUser);
	if (status != errSecSuccess) {
		throw_osxkeychainexception(env, status);
		return;
	}

	/* Unpack the params. */
	jstring_unpack(env, serviceName, &service_name);
	jstring_unpack(env, accountName, &account_name);
	if (service_name.str == NULL || 
	    account_name.str == NULL) {
		jstring_unpacked_free(env, serviceName, &service_name);
		jstring_unpacked_free(env, accountName, &account_name);
		return;
	}
	status = SecKeychainFindGenericPassword(
		NULL,
		service_name.len,
		service_name.str,
		account_name.len,
		account_name.str,
		NULL,
		NULL,
		&itemToDelete
	);
	if (status == errSecItemNotFound) {
        return;
    }
    else if (status != errSecSuccess) {
		throw_osxkeychainexception(env, status);
	}
	else {
		status = SecKeychainItemDelete(itemToDelete);
		if (status != errSecSuccess) {
			throw_osxkeychainexception(env, status);
		}
	}

	/* Clean up. */
	jstring_unpacked_free(env, serviceName, &service_name);
	jstring_unpacked_free(env, accountName, &account_name);
}
