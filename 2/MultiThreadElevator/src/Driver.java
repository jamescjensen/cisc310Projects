import java.util.ArrayList;


public class Driver {
	
	public static void main(String[] args) {
		int n = 8; // Number of elevators
		int f; // Number of floors
		String file; // Input file
		
//		ArrayList people = new ArrayList<Person>(1);
		ArrayList<Elevator> elevators = new ArrayList<Elevator>(1);
		
		
	
		
		// Create elevators
		for(int i = 0; i < n; i++) {
			elevators.add(new Elevator(0));
			System.out.println(elevators.get(i).getId());
		}
			
	}

}
