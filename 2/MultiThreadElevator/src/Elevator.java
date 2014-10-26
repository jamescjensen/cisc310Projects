public class Elevator implements Runnable {
	
	private static final int MAX_CAPACITY = 3;
	
	private static int nextId = 0;
	
	private Building 	building;
	private int 		id;
	private int 	currentFloor;
	private int 	currentNumPeople;
		
	public Elevator(int startFloor, Building building) {
		this.id = Elevator.nextId;
		Elevator.nextId++;
		
		this.currentFloor = 0;
		this.currentNumPeople = 0;	
		this.building = building;
		}
	
	
	
//	/** Opens the door of the elevator. Lets people out and gets people in
//	 */
//	public void open() {
//		System.out.println("Elevator " + this.getId() + " arrived at floor " + this.getCurrentFloor());
//		// TODO Let people go
//		// TODO Get People in
//		// TODO Close
//	}
//	
//	
//	/** Closes the door of the elevator
//	 */
//	private void close() {
//		System.out.println("Elevator " + this.getId() + " serviced floor " + this.getCurrentFloor());
//		// TODO Move()
//	}
//	
//	/** Moves the elevator either up or down 1 floor
//	 */
//	public void move() {
//		// Go either up or down
//		// Update the current floor
//	}

	@Override  
	public void run() {
		try {
			while(true) {
				Building.arrive();
				Thread.sleep(1000);
				Building.service();
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}		
	}
	
	
	// Getters and setters
	public int getId() { return this.id; }
		
	public int getCurrentFloor() { return this.currentFloor; }
	
	public Buidling getBuilding() { return this.building; }
	
	private void setCurrentFloor(int currentFloor) { this.currentFloor = currentFloor; }
	
	public int getCurrentNumPeople() { return this.currentNumPeople; }
	
	private void setCurrentNumPeople(int currentNumPeople) { this.currentNumPeople = currentNumPeople; }
	
}