import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;


public class Driver {
	
	public static void main(String[] args) throws IOException {
		Building building = new Building(1,2);
		String file = "src/input.txt"; // Input file

		ArrayList<Person> people = Driver.readFile(file,building);
		
		for(int i = 0; i < people.size(); i++) {
			new Thread(people.get(i)).start();;
		}
		
//		
////		ArrayList people = new ArrayList<Person>(1);
//		ArrayList<Elevator> elevators = new ArrayList<Elevator>(1);
//		
//		
//	
//		
//		// Create elevators
//		for(int i = 0; i < n; i++) {
//			elevators.add(new Elevator(0));
//			System.out.println(elevators.get(i).getId());
//		}
		
//		int[] floors = new int[3];
//		
//		floors[0] = 1;
//		floors[1] = 2;
//		floors[2] = 0;
//		
//		Person p1 = new Person("Tim", 5, 0, floors);
//		Person p2 = new Person("John", 10, 1, floors);
//		
//		new Thread(p1).start();
//		new Thread(p2).start();
		
	}
	
	/** Reads the input file and creates a person for each line
	 * */
	public static ArrayList<Person> readFile(String filename, Building building) throws IOException {
        ArrayList<Person> everyPerson = new ArrayList<Person>(1);
        Path path = Paths.get(filename);
        List<String> lines = Files.readAllLines(path, StandardCharsets.UTF_8);

        for(String line : lines) {
            String[] commandString = line.split(" ");

            String personName = "";
            int waitTime;
            int startFloor;
            int[] floorArray = new int[commandString.length-3];

            personName = commandString[0];
            waitTime = Integer.parseInt(commandString[commandString.length-2]);
            startFloor = Integer.parseInt(commandString[commandString.length-1]);
            
            for(int i=1;i<commandString.length-2;i++) {
                floorArray[i-1] = Integer.parseInt(commandString[i].replaceAll("[;\\]\\[]", ""));
            }
            
            Person p = new Person(building, personName, waitTime, startFloor, floorArray);
            everyPerson.add(p);
        }
        
        return everyPerson;
    }

}
