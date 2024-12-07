
public class s26169 {
    public static void main(String[] args) {
    	 int wrt = -12; 
         boolean inA = (wrt > -15 && wrt < -10);
         boolean inB = (wrt < -13);
         
         if (inA && !inB) {
             System.out.println("wrt należy tylko do zbioru A.");
         } else if (inB && !inA) {
             System.out.println("wrt należy tylko do zbioru B.");
         } else {
             System.out.println("wrt nie należy wyłącznie do jednego z tych zbiorów.");
         }
    }
}

