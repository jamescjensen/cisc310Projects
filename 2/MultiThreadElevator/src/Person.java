public class Person implements Runnable {
	
	private static final int WAITING = 1;
	private static final int IN_ELEVATOR = 0;
	
	private String 	name;
	private int 	waitTime;
	private int 	currentFloor;
	private int 	nextFloor;
	private int[] 	listFloor;
	
	public Person (String personName, int waitTime, int currentFloor, int[] listFloor) {
		this.name = personName;
		this.waitTime = waitTime;
		this.currentFloor = currentFloor;
		this.nextFloor = 0;
		this.listFloor = listFloor;
		
	}
	@Override
	public void run() {
		int[] listFloors = this.getListFloor();
		
		for(int i = 0; i < listFloors.length; i++) {
			System.out.println(this.getName() + " waiting on " + this.getCurrentFloor() + " for floor " + listFloors[i]);
			// TODO get on elevator
			// TODO travel
			// TODO get off elevator
			// TODO wait
//			building.goToFloor(listFloors[i]);
			
		}
		
				
	}
	
//	public void enterElevator(){
//		
//	}
//	
//	public void exitElevator() {
//		
//	}
	
	public String getName() {
		return this.name;
	}
	
	public int getNextFloor() { 
		return this.nextFloor;
	}
	
	public int getWaitTime() {
		return this.waitTime; 
	}
	
	public int getCurrentFloor() {
		return this.currentFloor;
	}
	
	private void setCurrentFloor(int floor) {
		this.currentFloor = floor;
	}
	
	public int[] getListFloor() {
		return this.listFloor;
	}
	
}
