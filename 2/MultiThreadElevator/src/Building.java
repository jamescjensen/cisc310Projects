import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class Building {
	
//	private List<Elevator> elevators = new ArrayList<Elevator>();
	private Elevator 		elevator;
	private int 			floors = 100000; // Default number of floors
	 
	private Lock 			elevatorsAvaliableLock;
	private Condition 		availableCondition;
	
	public Building(int e, int f) {
//		for(int i=0;i<e;i++){
//			elevators.add(new Elevator(i));
//			new Thread(elevators.get(i)).start();
//		}
		
		this.floors = f;
		this.elevatorsAvaliableLock = new ReentrantLock();
		this.availableCondition = elevatorsAvaliableLock.newCondition(); // Condition tied to lock
		this.elevator = new Elevator(0, this);
		
		// Start elevator thread
		new Thread(elevator).start();
	}
	
	/** Called by the person object when they want to get on the elevator
	 */
	public void getOnElevator(Person person) throws InterruptedException {
		// TODO Lock what??
		this.getElevatorsAvaliableLock().lock();
		
		try {	
			// Wait until the elevator is not on the same floor
			while(person.getCurrentFloor() != this.getElevator().getCurrentFloor() ||
					this.getElevator().getCurrentNumPeople() >= this.getElevator().getMaxCapacity()) { // TODO or the elevator is not going on the direction they want to go
				// Wait
				this.getAvailableCondition().await();
			}
			
			System.out.println(person.getName() + " taking elevator " + this.getElevator().getId());
			// Put person in the elevator
			this.getElevator().insertPerson(person);
		}
		finally {
			// Release the lock
			this.getElevatorsAvaliableLock().unlock();			
		}
	}
	
	/** Executes the elevator logic
	 */
	public void service() {
		// TODO Lock on what??
		this.getElevatorsAvaliableLock().lock();
		
		try {
			// Move the elevator by 1 floor
			this.getElevator().move();
			
			System.out.println("Elevator " + this.getElevator().getId() + " arrived at floor " + this.getElevator().getCurrentFloor());
			
			// Check the people that have arrived to their desired floor
			ArrayList<Person> peopleToRemove = new ArrayList<Person>();
			
			for(int i = 0; i < this.getElevator().getPeopleInElevator().size(); i++) {
				// Get the person
				Person person = this.getElevator().getPeopleInElevator().get(i);
				
				// If the person is in their destination floor, add to the list to remove
				if(person.getListFloor()[person.getNextFloor()] == this.getElevator().getCurrentFloor()) {
					peopleToRemove.add(person);
				}
								
			}
			
			for(int j = 0; j < peopleToRemove.size(); j ++) {
				// Remove person
				this.getElevator().removePerson(peopleToRemove.get(j));
				
				// Update the person's current floor
				peopleToRemove.get(j).updateFloor(this.getElevator().getCurrentFloor());
				
				System.out.println(peopleToRemove.get(j).getName() + " arrived at floor " + peopleToRemove.get(j).getCurrentFloor());
				// TODO Now the person should sleep and continue
			}
			
			
			// TODO might not work if things happen to fast. We got: 
			// Exception in thread "Thread-0" java.lang.NullPointerException
			// Signal all waiting people that the elevator has arrived to a floor
			this.availableCondition.signalAll(); // What if there is no space? Check for that?
						
			
			// If the elevator has reached the last floor or the first floor, switch directionss
			if(this.getElevator().getCurrentFloor() == this.getFloors() || this.getElevator().getCurrentFloor() == 0) {
				this.getElevator().changeDirection();
			}
		}
		finally {
			// Release the lock
			this.getElevatorsAvaliableLock().unlock();
		}
	}
	
	// Getters	
	public int getFloors() { return this.floors; }
	
	public Elevator getElevator() { return this.elevator; }

	public Lock getElevatorsAvaliableLock() {
		return this.elevatorsAvaliableLock;
	}

	public Condition getAvailableCondition() {
		return this.availableCondition;
	}

	// Setters
	public void setElevatorsAvaliableLock(Lock elevatorsAvaliableLock) {
		this.elevatorsAvaliableLock = elevatorsAvaliableLock;
	}

	public void setAvailableCondition(Condition availableCondition) {
		this.availableCondition = availableCondition;
	}
	
}
