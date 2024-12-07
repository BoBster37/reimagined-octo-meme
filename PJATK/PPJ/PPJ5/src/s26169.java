import java.util.Scanner;

public class s26169 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int kierunek = 0; 
        String[] kierunki = {"Północ", "Wschód", "Południe", "Zachód"};
        char[] strzalki = {'↑', '→', '↓', '←'};
        
        System.out.println("Początkowy kierunek: " + kierunki[kierunek] + " " + strzalki[kierunek]);

        while (true) {
            System.out.print("Wpisz A (lewo) lub D (prawo), X aby zakończyć: ");
            char c = in.next().charAt(0);

            if (c == 'A' || c == 'a') {
                kierunek = (kierunek + 3) % 4; 
            } else if (c == 'D' || c == 'd') {
                kierunek = (kierunek + 1) % 4; 
            } else if (c == 'X' || c == 'x') {
                System.out.println("Zakończenie programu.");
                break;
            } else {
                System.out.println("Nieprawidłowy znak. Proszę wpisać A, D lub X.");
                continue;
            }

            System.out.println("→" + c);
            System.out.println(kierunki[kierunek] + " " + strzalki[kierunek]);
        }
        
        in.close();
    }
}
