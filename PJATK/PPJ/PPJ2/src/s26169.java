
public class s26169 {    
   
    public static void main(String[] args) {
    	int a1 = 0x6D;        
        int a2 = 0x0D;        
        int a = a1 & a2;      
        
        int b1 = 0xA;        
        int b2 = 0xF;        
        int b = b1 | b2;     
        
        int c1 = 11 << 2;     
        int c2 = 6;           
        int c = c1 ^ c2;    
        
        System.out.println(a + " " + b + " " + c);  
      
    }
}
