public class s26169 {
    public static void main(String[] args) {
        // Tworzenie dwuwymiarowej tablicy znaków o rozmiarach równych różnicy między 'z' i 'a'.
        char[][] chars = new char['z' - 'a']['z' - 'a'];

        // Wypełnianie tablicy kolejnymi literami alfabetu.
        for (int i = 0; i < chars.length; i++) {
            char c = 'a'; // Inicjalizacja litery od 'a'.
            for (int j = 0; j < chars.length; j++, c++) {
                chars[i][j] = c; // Przypisywanie kolejnych liter.
            }
        }

        // Drukowanie wartości tablicy z przesunięciem indeksu o wielkość 'step'.
        for (int i = 0, step = 1; i < chars.length; step = (step << 1) % chars[i].length, i++) {
            // Wartość 'step' jest podwajana na każdym kroku, a potem modulo długość wiersza.
            System.out.println(chars[i][step]);
        }
    }
}

/*
Analiza programu:
1. Program tworzy tablicę dwuwymiarową `chars` o wymiarach 26x26, ponieważ różnica między 'z' (122) a 'a' (97) wynosi 26.
2. Tablica jest wypełniana znakami alfabetu od 'a' do 'z' w każdym wierszu.
3. W pętli drukującej:
   - `step` jest inicjalizowany wartością 1 i podwajany na każdym kroku (`step << 1`).
   - Po każdym podwojeniu `step` jest obliczane modulo długość wiersza, aby pozostać w granicach indeksów wiersza.
4. Program wypisuje znak z każdej kolejnej linii `chars` na pozycji obliczonej jako `step`.
5. Wynik końcowy to znaki tablicy zgodnie z przeskokami zdefiniowanymi przez `step`.
*/
