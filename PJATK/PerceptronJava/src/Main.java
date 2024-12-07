import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {
    public static void main(String[] args) {

        List<List<String>> train = getArray("perceptron.data");
        List<List<String>> test = getArray("perceptron.test.data");
        Scanner scanner = new Scanner(System.in);

        boolean bool = true;
        while (bool){

            System.out.println("[1] Testowanie własnego wektora");
            System.out.println("[2] Testowanie danych z pliku");
            System.out.println("[3] Zamknij");
            String choice = scanner.nextLine();
            if(choice.equals("1")){
                System.out.println("Podaj wektor\n");
                String vec = scanner.nextLine();
                String[] vecArray = vec.split(" ");
                List<String> list = new ArrayList<>(Arrays.asList(vecArray));
                int result = testingVec(list,training(train,500));
                if (result == 1 ){
                    System.out.println("Iris-virginica");
                }else {
                    System.out.println("Iris-versicolor");
                }
            } else if (choice.equals("2")) {
                int correct = 0;
                Pair weights = training(train, 500);
                for(int i = 0; i < test.size(); i ++){

                    List<String> tst = new ArrayList<>();

                    for(int k = 0; k < test.get(i).size() - 1; k ++){
                        tst.add(test.get(i).get(k));
                    }
                    int result = testingVec(tst,weights);

                    if((result == 1 && test.get(i).get(test.get(i).size() - 1).equals("Iris-virginica")) || (result == 0 && test.get(i).get(test.get(i).size() - 1).equals("Iris-versicolor"))  ) {
                        correct++;
                    }

                }

                double accuracy = (100.0/test.size())*correct;
                System.out.println("accuracy: " + accuracy + " %");

            } else if(choice.equals("3")){
                System.exit(0);
            }

        }

    }
    public static int testingVec (List<String> test, Pair pair){
        if (test.size() < pair.getList().size()){
            int diff = pair.getList().size() - test.size();
            for (int i = 0; i < diff; i ++){
                test.add("0");
            }
        }else if(pair.getList().size() < test.size()){
            int diff =  test.size() - pair.getList().size();
            for (int i = 0; i < diff; i ++){
                pair.addToList(0);
            }
        }
        int net = 0;
        for (int k = 0; k < test.size(); k ++){
            net += Double.parseDouble(test.get(k) ) * pair.getList().get(k);
        }
        net -= pair.getDb();
        int y = 0;
        if(net >= 0){
            y = 1;
        }
        return y;
    }
    public static Pair training(List<List<String>> train, int numb){
        List<Double> wagi = new ArrayList<Double>();
        List<String> trainFirst = train.get(0);
        double odch = (int) Math.round(Math.random());
        double ucz = 0.1;
        for(int x = 0; x < trainFirst.size() - 1; x ++){
            double random = (int) Math.round(Math.random());
            wagi.add(random);
        }
        for(int k = 0; k < numb; k ++) {
            for (int i = 0; i < train.size(); i++) {
                double net = 0;
                for (int j = 0; j < train.get(i).size() - 1; j++) {
                    net += Double.parseDouble(train.get(i).get(j)) * wagi.get(j);
                }
                net -= odch;
                int y = 0;
                if (net >= 0) {
                    y = 1;
                }
                int d = 0;
                if (train.get(i).get(train.get(i).size() - 1).equals("Iris-virginica")) {
                    d = 1;
                }

                odch = odch - ucz * (d - y);
                for(int waga = 0; waga < wagi.size(); waga ++){
                    double tr = Double.parseDouble(train.get(i).get(waga));
                    double element = wagi.get(waga) + ucz*(d - y)* tr;
                    wagi.set(waga,element);
                }
            }


        }
        Pair wach = new Pair(wagi, odch);
        return wach;
    }
    public static List<List<String>> getArray(String path){
        List<List<String>> resultArray = new ArrayList<List<String>>();
        try {
            File myObj = new File(path);
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();

                List<String> list = Arrays.asList(data.split(","));
                resultArray.add(list);
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        return resultArray;
    }
}