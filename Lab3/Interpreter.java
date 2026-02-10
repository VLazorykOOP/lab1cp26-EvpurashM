package Lab3;
// Інтерфейс
interface Expression {
    boolean interpret(String context);
}

// Реалізація
public class Interpreter implements Expression { // Можна назвати клас Interpreter або TermExpression
    private String data;

    public Interpreter(String data) {
        this.data = data;
    }

    @Override
    public boolean interpret(String context) {
        return context.contains(data);
    }
}