class CentralProcessingUnit{
    String brand;
    String model;
    double speed;
    int numCores;

    public CentralProcessingUnit(String brand, String model, double speed, int numCores){
        this.brand = brand;
        this.model = model;
        this.speed = speed;
        this.numCores = numCores;
    }

    double getParallelSpeed(){
        return speed*numCores;
    }

    String getDescription(){
        return "CPU: brand = " + brand + ", model = " + model + ", speed = " + speed + "GHz, " + "numCores = " + numCores + ", parallel speed = " 
        + getParallelSpeed() + "GHz."; 
    }

}

class Memory{
    String brand;
    String type;
    double size;
    double speed;
    int numSlots;

    public Memory(String brand, String type, double size, double speed, int numSlots){
        this.brand = brand;
        this.type = type;
        this.size = size;
        this.speed = speed;
        this.numSlots = numSlots;
    }

    double getTotalSize(){
        return size*numSlots;
    }

    double getParallelSpeed(){
        return speed*numSlots;
    }

    String getDescription(){
        return "Memory: brand = " + brand + ", type = " + type + ", size = " + size + ", speed = " + speed + "GHz, numSlots = " + numSlots + ", total size = " + 
        getTotalSize() + "GB" + ", velocidade paralela = " + getParallelSpeed() + "GHz.";
    }
}

class Disk{
    String brand;
    String type;
    double capacity;
    int rpm;

    public Disk(String brand, String type, double capacity, int rpm){
        this.brand = brand;
        this.type = type;
        this.capacity = capacity;
        this.rpm = rpm;
    }

    String getDescription(){
        return "Disk: brand = " + brand + ", type = " + type + ", capacity = " + capacity + "GB, rpm = " + rpm + "rpm";
    }
}

public class Computer {
    String manufacturer;
    CentralProcessingUnit cpu;
    Memory mem;
    Disk dsk;

    public Computer(String manufacturer, CentralProcessingUnit cpu, Memory mem, Disk dsk){
        this.manufacturer = manufacturer;
        this.cpu = cpu;
        this.mem = mem;
        this.dsk = dsk;
    }

    String getDescription(){
        return "Manufacturer: " + manufacturer + "\n" + cpu.getDescription() + mem.getDescription() + dsk.getDescription();
    }

    public static void main(String args[]){
        CentralProcessingUnit cpu = new CentralProcessingUnit("Intel", "i7", 3.2, 8);
        Memory mem = new Memory("Kingston", "DDR4", 8, 3.2, 4);
        Disk dsk = new Disk("Western Digital", "HDD", 4000, 9600);
        Computer comp = new Computer("Dell", cpu, mem, dsk);
        System.out.println(comp.getDescription());
    }
    
}
