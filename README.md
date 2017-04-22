# jKeychain [ ![Download](https://api.bintray.com/packages/davidafsilva/maven/jkeychain/images/download.svg) ](https://bintray.com/davidafsilva/maven/jkeychain/_latestVersion)


This is a fork of [conormcd/osx-keychain-java](https://github.com/conormcd/osx-keychain-java), 
which has been modified in the following fashion:
1. Removed *InternetPassword methods
2. Updated *GenericPassword to not thrown an exception when the key was not found
3. Refactored packaging 
4. "Gradelized" project
5. Published to OSS Repository

#### Maven 

Available repos:
* [bintray/davidafsilva](https://dl.bintray.com/davidafsilva/maven)
* [jCenter](https://jcenter.bintray.com/)
```XML
<dependency>
  <groupId>pt.davidafsilva.apple</groupId>
  <artifactId>jkeychain</artifactId>
  <version>1.0.0</version>
</dependency>
```

#### Gradle 
```groovy
compile 'pt.davidafsilva.apple:jkeychain:1.0.0'
```

### Usage:

```java
final OSXKeychain keychain = OSXKeychain.getInstance();
final Optional<String> mySecret = keychain.findGenericPassword("mySecret", "username");
```
