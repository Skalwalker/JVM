public class ExcepTest {
    public static void arrayoutbounds() {
        int a[] = new int[2];
        a[-1] = 0;
        // System.out.println(a[3]);
    }

    public static void arraynull() {
        int a[] = null;
        a[3] = 7;
    }

    public static void arraystore() {
        Object[] s = new Puppy[2];
        s[0] = new Catto();
    }

    public static void arithmetic() {
        float a = (3.0f / 0.0f);
    }

   public static void main(String[] args) {
       arraystore();
   }
}
