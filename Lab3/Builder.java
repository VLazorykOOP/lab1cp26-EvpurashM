package Lab3;
// Абстрактний будівельник
abstract class StudBuilder {
    protected Stud stud;

    public void createNewStud() { stud = new Stud(); }
    public Stud getStud() { return stud; }

    public abstract void buildType();
    public abstract void buildStipend(double amount);
    public abstract void buildId(int id);
}

// Будівельник для відмінників
class AStudBuilder extends StudBuilder {
    public void buildType() { stud.setType(StudType.EXCELLENT); }
    public void buildStipend(double amount) { stud.setStipend(amount); }
    public void buildId(int id) { stud.setId(id); }
}
// Будівельник для звичайних
class NormalStudBuilder extends StudBuilder {
    public void buildType() { stud.setType(StudType.NORMAL); }
    public void buildStipend(double amount) { stud.setStipend(amount); }
    public void buildId(int id) { stud.setId(id); }
}

// Director (Керівник)
class Director {
    private StudBuilder builder;

    public void setBuilder(StudBuilder builder) { this.builder = builder; }

    public Stud buildStud(int id, double stipend) {
        builder.createNewStud();
        builder.buildId(id);
        builder.buildType();
        builder.buildStipend(stipend);
        return builder.getStud();
    }
}