
public class Person implements Runnable {
	
	private static final int WAITING = 1;
	private static final int IN_ELEVATOR = 0;
	
	private String personName;
	private int waitTime;
	private int currentFloor;
	private int nextFloor;
	private int[] listFloor;
	
	public Person (String personName, int waitTime, int currentFloor, int[] listFloor) {
		this.personName = personName;
		this.waitTime = waitTime;
		this.currentFloor = currentFloor;
		this.nextFloor = 0;
		this.listFloor = listFloor;
		
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		
	}
	
	public void enterElevator(){
		
	}
	
	public void exitElevator() {
		
	}
	
	public String getPersonName() {
		return this.personName;
	}
	
	public int getNextFloor() { 
		return this.nextFloor;
	}
	
	public int getwaitTime() {
		return this.waitTime; 
	}
	
	public int getcurrentFloor() {
		return this.currentFloor;
	}
	
	public int[] getListFloor() {
		return this.listFloor;
	}
	

	/* Person runnable
	 * @param FloorArray array of floors 
	 * @param timeSpent time spent by the person on each floor
	 * @param Start Floor of the person
	 */
	
	
		
	// Print 
    

}
