
public class Person implements Runnable {
	
	private static final int WAITING = 1;
	private static final int IN_ELEVATOR = 0;
	
	private String PersonName;
	private int waitTime;
	private int currentFloor;
	private int[] listFloor;
	
	public Person (String PersonName, int waitTime, int currentFloor, int[] ListFloor) {
		
		this.PersonName = PersonName;
		this.waitTime = waitTime;
		this.currentFloor = currentFloor;
		this.listFloor = ListFloor;
		
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		
	}
	
	public void EnterElevator(){
		
	}
	
	public void ExitElevator() {
		
	}
	
	public String GetPersonName() {
		return this.PersonName;
	}
	
	public int GetwaitTime() {
		return this.waitTime; 
	}
	
	public int GetcurrentFloor() {
		return this.currentFloor;
	}
	
	public int[] GetListFloor() {
		return this.listFloor;
	}
	

	/* Person runnable
	 * @param FloorArray array of floors 
	 * @param timeSpent time spent by the person on each floor
	 * @param Start Floor of the person
	 */
	
	
		
	// Print 
    

}
