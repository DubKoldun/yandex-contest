KTFLAGS=-include-runtime -d
KTC=kotlinc
DS=src/DS/Cell.kt src/DS/Grid.kt
SRC=src/Main.kt $(DS)


all: jar

run: jar
	java -jar run.jar

jar:
	$(KTC) $(SRC) $(KTFLAGS) run.jar 

clean:
	rm -rf *.jar
