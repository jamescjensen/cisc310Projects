import java.util.ArrayList;
import java.util.List;


public class Building {
	
	List<Elevator> elevators = new ArrayList<Elevator>();
	int f = 100000; // Number of floors
	
	public Building(int e, int f) {
		for(int i=0;i<e;i++){
			elevators.add(new Elevator(i));
			new Thread(elevators.get(i)).start();
		}
		setF(f);
	}

	public void getOnElevator(Person person) {
		System.out.println(person.getName() + " taking elevator ");
	}
	
	
	public void move() {
		
	}
	
	public int getF(){
		return this.f;
	}
	
	public void setF(int f){
		this.f = f;
	}

}
