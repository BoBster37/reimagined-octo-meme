import java.util.List;

public class Pair {
    private List<Double> list;
    private Double db;
    public Pair(List<Double> map, double db){
        this.list = map;
        this.db = db;
    }

    public Double getDb() {
        return db;
    }

    public List<Double> getList() {
        return list;
    }

    public void setDb(Double db) {
        this.db = db;
    }

    public void setList(List<Double> list) {
        this.list = list;
    }

    public void addToList(double doub){
        list.add(doub);
    }
}
