package Lab3;
import java.util.List;

// Старий принтер (Adaptee)
class LegacyPrinter {
    public void printStud(Stud s) {
        System.out.println("Info: " + s.toString());
    }
}

// Інтерфейс, який нам потрібен
interface StudListPrinter {
    void print(List<Stud> list);
}

// Адаптер
public class Adapter implements StudListPrinter {
    private LegacyPrinter legacyPrinter = new LegacyPrinter();

    @Override
    public void print(List<Stud> list) {
        System.out.println("--- Список студентів (Adapter) ---");
        for (Stud s : list) {
            legacyPrinter.printStud(s);
        }
    }
}