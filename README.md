# jKeychain

This is a fork of [conormcd/osx-keychain-java](https://github.com/conormcd/osx-keychain-java), 
which has been modified in the following fashion:
1. Removed *InternetPassword methods
2. Updated *GenericPassword to not thrown an exception when the key was not found
3. Refactored packaging 
4. "Gradelized" project
5. TODO: publish to a OSS Repository

### Usage:

```java
final OSXKeychain keychain = OSXKeychain.getInstance();
final Optional<String> mySecret = keychain.findGenericPassword("mySecret", "username");
```
