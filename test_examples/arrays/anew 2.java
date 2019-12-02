
class multi{
	public static void main(String argv[]){
		String vetor_int[] = new String[5];
        String k;
        k = "omawe";
		/*Seta a matriz de ints*/
		for (int i = 0; i < vetor_int.length; i++){
			vetor_int[i] = k;
		}

        for (int i = 0; i < 5; i++){
			System.out.println(vetor_int[i]);
		}
    }
}
