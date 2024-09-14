package parte1;
import java.awt.EventQueue;
import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class MainServidor {
	
	public static void main(String[] args) {
		try {
			// Inicializo el controlador
			HormigaController controlador = new HormigaController();
			new Thread(new ThreadGroup("HilosControladores"), controlador).start();
			//Arranca el espacio de nombres RMIRegistry local en el puerto 1099. No es obligatorio
			Registry registry = LocateRegistry.createRegistry(1099);
			//Hace visible el objeto para clientes
			Naming.rebind("//127.0.0.1/ControladorHormiga", controlador);
			System.out.println("El controlador ha quedado registrado.");
			
			/**
			 * Launch the GUI application.
			 */
			
			EventQueue.invokeLater(new Runnable() {
				public void run() {
					try {
						GUI window = new GUI(controlador);
						window.getFrmAplicacinHormigas().setVisible(true);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			});
			
			System.out.println("Se ha creado la GUI.");
		} catch (Exception e) {e.printStackTrace();}
		
	}

}
