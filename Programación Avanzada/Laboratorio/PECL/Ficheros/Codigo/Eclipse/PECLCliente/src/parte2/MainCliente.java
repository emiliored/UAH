package parte2;
import java.awt.EventQueue;
import java.rmi.Naming;
import parte2.interfaces.VistaClienteRMI;

public class MainCliente {
	
	public static void main(String[] args) {
		
		//	Inicializo el controlador
		try {
			VistaClienteRMI controlador = (VistaClienteRMI) Naming.lookup("//127.0.0.1/ControladorHormiga");
			
			/**
			 * Launch the GUI application.
			 */
			
			EventQueue.invokeLater(new Runnable() {
				public void run() {
					try {
						GUICliente window = new GUICliente(controlador);
						window.getFrmAplicacinHormigas().setVisible(true);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			});
			
		} catch (Exception e) {e.printStackTrace();}
		
	}

}
