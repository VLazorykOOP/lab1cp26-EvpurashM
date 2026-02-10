package Lab3;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Stud> ST = new ArrayList<>();
        
        Director director = new Director();
        StudBuilder aBuilder = new AStudBuilder();
        StudBuilder nBuilder = new NormalStudBuilder();

        // Використовуємо наш клас Interpreter (або TermExpression, як ви його назвали у файлі 2)
        Interpreter isA = new Interpreter("5");

        for (int i = 0; i < 100; ++i) {
            if (isA.interpret(Integer.toString(i))) {
                director.setBuilder(aBuilder);
                ST.add(director.buildStud(i, 1500));
            } else {
                director.setBuilder(nBuilder);
                ST.add(director.buildStud(i, 1000));
            }
        }

        Adapter printer = new Adapter();
        printer.print(ST);
    }
}