SET CLASSPATH=.;C:\Javalib\antlr-4.5.2-complete.jar;%CLASSPATH%

doskey antlr4=java org.antlr.v4.Tool $*

doskey grun =java org.antlr.v4.runtime.misc.TestRig $*

antlr4 Cactus.g4

javac Cactus*.java

grun Cactus token -tree < test.txt