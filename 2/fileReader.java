import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.lang.Iterable;
import java.util.List;
import java.util.Arrays;
import java.io.IOException;
import java.nio.charset.StandardCharsets;

class Demo {

    public static void main(String[] args) throws IOException {
        fileReader fr = new fileReader();
        fr.readFile("input.txt");
    }
}

class fileReader {

    List<Person> readFile(String filename) throws IOException {

        List<Person> everyPerson;

        Path path = Paths.get(filename);
        List<String> lines = Files.readAllLines(path, StandardCharsets.UTF_8);

        for(String line : lines) {

            String[] commandString = line.split(" ");

            String personName = "";
            int waitTime;
            int endFloor;
            int[] floorArray = new int[commandString.length-3];

            personName = commandString[0];
            waitTime = Integer.parseInt(commandString[commandString.length-2]);
            endFloor = Integer.parseInt(commandString[commandString.length-1]);

            for(int i=1;i<commandString.length-2;i++) {
                floorArray[i-1] = Integer.parseInt(commandString[i].replaceAll("[;\\]\\[]", ""));
            }
            Person p = new Person(personName, waitTime, endFloor, floorArray);
            everyPerson.add(p);
        }
    }

    return everyPerson;

}

