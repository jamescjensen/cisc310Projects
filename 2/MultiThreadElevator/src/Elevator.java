public class Elevator implements Runnable {
	
	private static final int MAX_CAPACITY = 3;
	
	private static int nextId = 0;
	
	private int id;
	private int currentFloor;
	private int currentNumPeople;
		
	public Elevator(int startFloor) {
		Elevator.nextId++;
		
		this.id = Elevator.nextId;
		this.currentFloor = 0;
		this.currentNumPeople = 0;		
	}
	
	
	
	/** Opens the door of the elevator. Lets people out and gets people in
	 */
	public void open() {
		
	}
	
	
	/** Closes the door of the elevator
	 */
	public void close() {
		
	}
	
	/** Moves the elevator either up or down 1 floor
	 */
	public void move() {
		
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		
	}
	
	
	// Getters and setters
	public int getId() { return this.id; }
		
	public int getCurrentFloor() { return this.currentFloor; }
	
	private void setCurrentFloor(int currentFloor) { this.currentFloor = currentFloor; }
	
	public int getCurrentNumPeople() { return this.currentNumPeople; }
	
	private void setCurrentNumPeople(int currentNumPeople) { this.currentNumPeople = currentNumPeople; }
	
}
