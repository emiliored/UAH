package parte1;

import java.util.concurrent.atomic.AtomicInteger;

import parte1.Logging.LoggingException;
import parte1.interfaces.Hormiga;

public class HormigaObrera extends Thread implements Hormiga{
	
	// Define sus propios valores de clase
	protected static String idType = "HO";
	protected static ThreadGroup grupoHilos = new ThreadGroup("HilosHO");
	protected static AtomicInteger contador = new AtomicInteger(0);
	
	static {
		HormigaController.setHormigasObreras(grupoHilos);
	}
	
	// Atributos especificos de cada hormiga obrera
	private int idHormiga;
	private HormigaController controlador;
	
	// Métodos implementados en la interfaz
	@Override
	public String getIdType() {
		return idType;
	}
	@Override
	public int getIdHormiga() {
		return this.idHormiga;
	}
	
	@Override
	public HormigaController getControlador() {
		return this.controlador;
	}
	
	@Override
	public String getNombreHormiga() {
		return idType.concat(String.format("%04d", this.idHormiga));
	}
	
	
	// Métodos de clase específicos de la hormiga obrera
	
	// Métodos específicos para cada hormiga obrera	
	public HormigaObrera(HormigaController hormigaController) throws LoggingException{
		super(grupoHilos, "");
		this.idHormiga = contador.getAndIncrement();
		this.controlador = hormigaController;
		super.setName(this.getNombreHormiga());
		try {
			this.controlador.addLog(this, ", creación de la hormiga obrera.");
		} catch (InterruptedException e) {
			throw new Logging.LoggingException(e.getMessage());
		}
	}

	// Override de los métodos de la clase Thread
	@Override
	public void run() {
		// Comportamiento que harán todas las hormigas al nacer.
		try {
			this.controlador.addLog(this, ", acaba de nacer...");
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		this.controlador.pasarTunelEntrada(this);
		// Conportamiento específico de cada hormiga.
		int i = 0;
		while(true) {
			if(this.controlador.getPararEjecucion().get()) { // Si está true, se suspende la hormiga.
				this.suspend();
			}
			/*Accede al ALMACÉN DE COMIDA para coger cinco elementos de comida requiriendo entre 1 y 2 
			 * segundos. Entonces, viaja hacia la ZONA PARA COMER, tardando un tiempo aleatorio de 
			 * entre 1 y 3 segundos. A continuación, accede a la ZONA PARA COMER y deposita el elemento 
			 * de comida, consumiendo entre 1 y 2 segundos. Desde este momento, elemento de comida 
			 * está disponible para ser ingerido por cualquier hormiga de la colonia.
			 */
			if(this.getIdHormiga() % 2 == 0) { // Hormiga obrera par
				this.controlador.entrarAlmacenComidaConsumir(this);
				this.controlador.transicionZonaComer(this);
				this.controlador.entrarZonaComerDepositar(this, 5);
			}
			/* Acude a la zona exterior de la colonia a coger cinco elementos de comida y 
			 * lo lleva al interior de la colonia, tardando 4 segundos. A continuación, 
			 * lo deposita en el ALMACÉN DE COMIDA, tardando un tiempo aleatorio de entre 2 
			 * y 4 segundos. A este ALMACÉN DE COMIDA sólo pueden acceder simultáneamente 
			 * 10 hormigas
			 */
			else { // Hormiga obrera impar
				this.controlador.pasarTunelSalida(this); // Está fuera
				this.controlador.transicionBuscandoComida(this); // Buscar comida fuera
				this.controlador.pasarTunelEntrada(this); // Vuelve a entrar
				this.controlador.entrarAlmacenComidaDepositar(this); // Guarda la comida en el almacen
			}
			i++;
			/*
			 * Todas las hormigas obreras, pares o impares, tras realizar 10 iteraciones completas 
			 * de su acción principal, pasan por la ZONA PARA COMER para reponer fuerzas y comer, 
			 * consumiendo 1 unidad de alimento y tardando 3 segundos. A continuación, acceden a 
			 * la ZONA DE DESCANSO, consumiendo allí 1 segundo, para, a continuación, volver a 
			 * retomar su actividad habitual.
			 */
			if(i == 10) {
				i = 0;
				this.controlador.entrarZonaComerConsumir(this);
				this.controlador.entrarZonaDescanso(this, 1);
			}
		}
	}
}
