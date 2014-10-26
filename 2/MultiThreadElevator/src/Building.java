
public class Building {
	
	int e = 2; // Number of elevators
	int f = 5; // Number of floors
	
	public Building(int e, int f) {
		setE(e);
		setF(f);
	}

	public int getE(){
		return this.e;
	}
	
	public void setE(int e){
		this.e = e;
	}
	
	public int getF(){
		return this.f;
	}
	
	public void setF(int f){
		this.f = f;
	}
	
	public void getOnElevator(String name) {
		System.out.println(name + " taking elevator ");
		
	}
	
	public void getOffElevator(String name, int floor) {
		System.out.println(name + " arrived at floor " + floor);
	}

}
