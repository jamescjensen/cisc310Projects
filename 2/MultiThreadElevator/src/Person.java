import java.util.ArrayList;
import java.util.List;

public class Person implements Runnable {
	
	private static final boolean WAITING = true;
	private static final boolean IN_ELEVATOR = false;
	
	private String 		name;
	private Building	building;
	private int 		waitTime;
	private int 		currentFloor;
	private int 		nextFloor;
	private int[] 		listFloor;
	private boolean 	status;
	
	public Person (Building building, String personName, int waitTime, int currentFloor, int[] listFloor) {
		this.name = personName;
		this.building = building;
		this.waitTime = waitTime;
		this.currentFloor = currentFloor;
		this.nextFloor = 0;
		this.listFloor = listFloor;
		this.status = WAITING;
		
	}
	@Override
	public void run() {
		int[] listFloors = this.getListFloor();
		
		try {

			for(int i = 0; i < listFloors.length; i++) {
				System.out.println(this.getName() + " waiting on " + this.getCurrentFloor() + " for floor " + listFloors[i]);
				getBuilding().getOnElevator(this);
				System.out.println(this.getName() + " arrived on floor " + this.getCurrentFloor());
				Thread.sleep(this.getWaitTime());
			}
		}
		catch(InterruptedException ie) {
			ie.printStackTrace();
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
	
	public Building getBuilding() {
		return this.building;
	}
	
	public boolean getStatus() {
		return this.status;
	}
	
	public boolean getWaiting() {
		return Person.WAITING;
	}
	
	public boolean getInElevator() {
		return Person.IN_ELEVATOR;
	}
	
	public void setStatus(boolean status) {
		this.status = status;
	}
	
	private void setCurrentFloor(int floor) {
		this.currentFloor = floor;
	}
	
	public int[] getListFloor() {
		return this.listFloor;
	}
	
}
