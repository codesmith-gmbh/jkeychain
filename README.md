# osx-keychain-java

This is a fork of [conormcd/osx-keychain-java](https://github.com/conormcd/osx-keychain-java), 
which has been modified in the following fashion:
1. Removed *InternetPassword methods
2. Updated *GenericPassword to not thrown an exception when the key was not found
3. Refactored packaging 
4. "Gradelized" project


### Usage:
    OSXKeychain keychain = OSXKeychain.getInstance();
    Optional<String> password = keychain.findGenericPassword("key", "username");
