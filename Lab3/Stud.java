package Lab3;
import java.util.ArrayList;
import java.util.List;

// Типи студентів
enum StudType {
    EXCELLENT, 
    NORMAL
}

// Клас студента
public class Stud {
    private int id;
    private double stipend;
    private StudType type;

    public void setId(int id) { this.id = id; }
    public void setStipend(double stipend) { this.stipend = stipend; }
    public void setType(StudType type) { this.type = type; }

    @Override
    public String toString() {
        return "Student{ID=" + id + ", Type=" + type + ", Stipend=" + stipend + "}";
    }
}