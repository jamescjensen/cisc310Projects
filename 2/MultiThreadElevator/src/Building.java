import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class Building {
	
//	private List<Elevator> elevators = new ArrayList<Elevator>();
	private Elevator el;
	private int f = 100000; // Number of floors
	 
	private Lock elevatorsAvaliableLock;
	private Condition availableCondition;
	
	
	
	public Building(int e, int f) {
//		for(int i=0;i<e;i++){
//			elevators.add(new Elevator(i));
//			new Thread(elevators.get(i)).start();
//		}
		
		this.el = new Elevator(0);
		
		new Thread(el).start();
		setF(f);
		
		this.elevatorsAvaliableLock = new ReentrantLock();
		this.availableCondition = elevatorsAvaliableLock.newCondition(); // Condition tied to lock
	}

	public void getOnElevator(Person person) throws InterruptedException {
		this.elevatorsAvaliableLock.lock();
		
		try {
////			while(true) {
////				for(Elevator elevator:elevators) {
//				
//					while(person.getCurrentFloor() != elevator.getCurrentFloor() && elevator.getCurrentNumPeople() >= elevator.getMaxCapacity()) {
//						this.availableCondition.await();
//					}
//					
////					break;
////				}
//					System.out.println(person.getName() + " taking elevator ");
//					
////					break;
//				
//			}
			
			while(person.getCurrentFloor() != el.getCurrentFloor() && el.getCurrentNumPeople() >= el.getMaxCapacity()) {
				this.availableCondition.await();
			}
			
			System.out.println(person.getName() + " taking elevator " + el.getId());
			person.setStatus(person.getInElevator());
			el.setCurrentNumPeople(el.getCurrentNumPeople() + 1);

		}
		finally {
			this.elevatorsAvaliableLock.unlock();
		}
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
