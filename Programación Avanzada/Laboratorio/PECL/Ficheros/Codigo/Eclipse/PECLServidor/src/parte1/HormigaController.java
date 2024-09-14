package parte1;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Set;
import java.util.concurrent.CopyOnWriteArraySet;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

import parte1.Logging.LoggingException;
import parte1.interfaces.Hormiga;
import parte1.interfaces.VistaHormigaGUI;
import parte2.interfaces.VistaClienteRMI;

public class HormigaController extends UnicastRemoteObject implements Runnable, VistaHormigaGUI, VistaClienteRMI {
	/**
	 * 
	 */
	private static final long serialVersionUID = 7811150400089455866L;
	// Semáforos para los tuneles
	private Semaphore semTunelEntrada;
	private Semaphore semTunelSalida;
	// Semáforos para las zonas compartidas;
	private Semaphore semAlmacenComida;
	private Semaphore semUnidadesAlmacenVacio;
	private Semaphore semUnidadesAlmacenExclusion;
	private Semaphore semUnidadesAlmacenLleno;
	private Semaphore semUnidadesZonaComer;
	// Semáforo para notificar a las hormigas cria
	private Semaphore semLuchandoInsecto;
	// Atributos
	private Logging log;
	// Semáforo para notificar el cambio en alguno de los recursos compartidos
	private Semaphore semCambioRecursos;
	// Recursos compartidos para saber donde estás las hormigas en cada zona
	private Set<String> hDentroColonia;
	private Set<String> hFueraColonia;
	private Set<String> hBuscandoComida;
	private Set<String> hRepeliendoInsecto;
	private Set<String> hAlmacenComida;
	private Set<String> hLlevandoZonaComer;
	private Set<String> hZonaInstruccion;
	private Set<String> hZonaDescanso;
	private Set<String> hZonaComer;
	private Set<String> hRefugio;
	// Recursos compartidos para saber las unidades de comida
	private int unidadesComidaAlmacen;
	private AtomicInteger unidadesComidaZonaComer;
	// Atributo para poder parar la ejecución del hormiguero
	private AtomicBoolean pararEjecucion;
	// Atributos estáticos para obtener los grupos de hilos de las hormigas
	private static ThreadGroup hormigasObreras;
	private static ThreadGroup hormigasSoldado;
	private static ThreadGroup hormigasCria;
	// Atributo estático para generar un insecto invasor
	private static AtomicBoolean luchandoInsectoInvasor = new AtomicBoolean(false);

	public HormigaController() throws RemoteException{
		// Me creo la cola del Logging
		this.log = new Logging(new LinkedBlockingQueue<String>());
		// Semáforos para los túneles
		this.semTunelEntrada = new Semaphore(1,true);
		this.semTunelSalida = new Semaphore(2,true);
		// Semáforo para el cambio de los recursos compartidos
		this.semCambioRecursos = new Semaphore(0,true);
		// Semáforos para las zonas compartidas
		this.semAlmacenComida = new Semaphore(10,true);
		this.semUnidadesAlmacenVacio = new Semaphore(0,true);
		this.semUnidadesAlmacenExclusion = new Semaphore(1,true);
		this.semUnidadesAlmacenLleno = new Semaphore(this.semAlmacenComida.availablePermits(),true);
		this.semUnidadesZonaComer= new Semaphore(0,true);
		// Listas de Zonas
		this.hDentroColonia = new CopyOnWriteArraySet<String>();
		this.hFueraColonia = new CopyOnWriteArraySet<String>();
		this.hBuscandoComida = new CopyOnWriteArraySet<String>();
		this.hRepeliendoInsecto = new CopyOnWriteArraySet<String>(); 
		this.hAlmacenComida = new CopyOnWriteArraySet<String>(); 
		this.hLlevandoZonaComer = new CopyOnWriteArraySet<String>(); 
		this.hZonaInstruccion = new CopyOnWriteArraySet<String>(); 
		this.hZonaDescanso = new CopyOnWriteArraySet<String>();
		this.hZonaComer = new CopyOnWriteArraySet<String>();
		this.hRefugio = new CopyOnWriteArraySet<String>();
		// Unidades de comida común
		this.unidadesComidaAlmacen = 0;
		this.unidadesComidaZonaComer = new AtomicInteger(0);
		// Atributo para parar la ejecucion
		this.pararEjecucion = new AtomicBoolean(false);
		this.semLuchandoInsecto = new Semaphore(10000,true);
	}
	
	// Getter y Setters públicos
	public Set<String> gethDentroColonia() {
		return hDentroColonia;
	}

	public Set<String> gethFueraColonia() {
		return hFueraColonia;
	}

	public Set<String> gethBuscandoComida() {
		return hBuscandoComida;
	}

	public Set<String> gethRepeliendoInsecto() {
		return hRepeliendoInsecto;
	}

	public Set<String> gethAlmacenComida() {
		return hAlmacenComida;
	}

	public Set<String> gethLlevandoZonaComer() {
		return hLlevandoZonaComer;
	}

	public Set<String> gethZonaInstruccion() {
		return hZonaInstruccion;
	}

	public Set<String> gethZonaDescanso() {
		return hZonaDescanso;
	}

	public Set<String> gethZonaComer() {
		return hZonaComer;
	}

	public Set<String> gethRefugio() {
		return hRefugio;
	}
	
	public int getUnidadesComidaAlmacen() {
		return unidadesComidaAlmacen;
	}

	public void setUnidadesComidaAlmacen(int unidadesComidaAlmacen) {
		this.unidadesComidaAlmacen = unidadesComidaAlmacen;
	}

	public AtomicInteger getUnidadesComidaZonaComer() {
		return unidadesComidaZonaComer;
	}

	public void setUnidadesComidaZonaComer(AtomicInteger unidadesComidaZonaComer) {
		this.unidadesComidaZonaComer = unidadesComidaZonaComer;
	}
	public static ThreadGroup getHormigasObreras() {
		return hormigasObreras;
	}

	public static void setHormigasObreras(ThreadGroup hormigasObreras) {
		HormigaController.hormigasObreras = hormigasObreras;
	}

	public static ThreadGroup getHormigasSoldado() {
		return hormigasSoldado;
	}

	public static void setHormigasSoldado(ThreadGroup hormigasSoldado) {
		HormigaController.hormigasSoldado = hormigasSoldado;
	}

	public static ThreadGroup getHormigasCria() {
		return hormigasCria;
	}

	public static void setHormigasCria(ThreadGroup hormigasCria) {
		HormigaController.hormigasCria = hormigasCria;
	}
	
	public static AtomicBoolean getLuchandoInsectoInvasor() {
		return luchandoInsectoInvasor;
	}

	public Semaphore getSemLuchandoInsecto() {
		return semLuchandoInsecto;
	}
	
	@Override
	public AtomicBoolean getPararEjecucion() {
		return pararEjecucion;
	}
	@Override
	public void pararEjecucion() {
		this.pararEjecucion.compareAndSet(false, true);
	}
	@Override
	public void continuarEjecucion() {
		if(this.pararEjecucion.getAndSet(false) == true) { // Si el valor anterior era true
			try {
				hormigasObreras.resume();
				hormigasSoldado.resume();
				hormigasCria.resume();
			} catch(IllegalMonitorStateException e) {}
			
		}
	}
	
	@Override
	public void generarInsectoInvasor() {
		if(luchandoInsectoInvasor.getAndSet(true) == false) {
			if(this.pararEjecucion.get()) {
				luchandoInsectoInvasor.set(false);
				return;
			}
			this.semLuchandoInsecto.drainPermits();
			hormigasSoldado.interrupt();
			hormigasCria.interrupt();
			new Thread(Thread.currentThread().getThreadGroup(),
				new Runnable() {
					@Override
					public void run() {
						try {
							Thread.sleep(20*1000);
						} catch (InterruptedException e) {}
						finally {
							luchandoInsectoInvasor.set(false);
							semLuchandoInsecto.release(10000);
						}
					}
			}, "HiloControlInsectoInvasor").start();;
		}
	}
	
	// Métodos sobreescritos de la interfaz VistaClienteRMI
	@Override
	public Set<String> gethDentroColoniaRMI() throws RemoteException {
		return this.gethDentroColonia();
	}

	@Override
	public Set<String> gethFueraColoniaRMI() throws RemoteException {
		return this.gethFueraColonia();
	}

	@Override
	public Set<String> gethZonaInstruccionRMI() throws RemoteException {
		return this.gethZonaInstruccion();
	}

	@Override
	public Set<String> gethRepeliendoInsectoRMI() throws RemoteException {
		return this.gethRepeliendoInsecto();
	}

	@Override
	public Set<String> gethZonaComerRMI() throws RemoteException {
		return this.gethZonaComer();
	}

	@Override
	public Set<String> gethRefugioRMI() throws RemoteException {
		return this.gethRefugio();
	}

	@Override
	public void generarInsectoInvasorRMI() throws RemoteException {
		this.generarInsectoInvasor();
	}

	@Override
	public void cambioAdquireRMI() throws InterruptedException, RemoteException {
		this.cambioAdquire();
	}

	@Override
	public void cambioReleaseRMI() throws RemoteException {
		this.cambioRelease();
		
	}
	
	@Override
	public void cambioAdquire() throws InterruptedException {
		this.semCambioRecursos.drainPermits();
		this.semCambioRecursos.acquire();
	}
	@Override
	public void cambioRelease() {
		this.semCambioRecursos.release();
	}

	// Métodos
	public void addLog(Hormiga hormiga, String mensaje) throws InterruptedException {
		log.getListaLog().put(Logging.getMensaje("La hormiga "+ hormiga.getNombreHormiga() + mensaje));
	}

	// 	Métodos para los túneles
	public void pasarTunelEntrada(Hormiga hormiga) {
		try {
			this.semTunelEntrada.acquire();
			this.hFueraColonia.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
			// Está la hormiga en el tunel
			this.addLog(hormiga, ", ha pasado por un tunel de entrada.");
			Thread.sleep(100);
			this.addLog(hormiga, ", ha salido por un tunel de entrada.");
		} catch(InterruptedException ie) {}
		finally {
			this.semTunelEntrada.release();
			this.hDentroColonia.add(hormiga.getNombreHormiga());
			this.cambioRelease();
		}
	}
	
	public void pasarTunelSalida(Hormiga hormiga) {
		try {
			this.semTunelSalida.acquire();
			this.hDentroColonia.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
			// Está la hormiga en el tunel
			this.addLog(hormiga, ", ha pasado por un tunel de salida.");
			Thread.sleep(100);
			this.addLog(hormiga, ", ha salido por un tunel de salida.");
		} catch(InterruptedException ie) {}
		finally {
			this.semTunelSalida.release();
			this.hFueraColonia.add(hormiga.getNombreHormiga());
			this.cambioRelease();
		}
	}
	
	// Métodos para controlar el acceso a las zonas compartidas.
	
	// Métodos hormigas obreras en zonas compartidas.
	public void transicionBuscandoComida(HormigaObrera hormiga) {
		try {
			this.addLog(hormiga, ", está buscando comida en el campo.");
			this.hBuscandoComida.add(hormiga.getName()); // Queda reflejado que está dentro del almacen
			this.cambioRelease();
			Thread.sleep(4*1000); // Tiempo que tarda en depositarlo
			this.addLog(hormiga, ", ha terminado de buscar comida y se prepara para entrar.");
		} catch(InterruptedException ie) {}
		finally {
			this.hBuscandoComida.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
		}
	}
	
	public void entrarAlmacenComidaDepositar(HormigaObrera hormiga) {
		try {
			this.semUnidadesAlmacenLleno.acquire();
			this.semAlmacenComida.acquire(); // Entra en el almacen de comida
			// Está la hormiga en el tunel
			this.addLog(hormiga, ", ha entrado al almacén de comida a depositar.");
			this.hAlmacenComida.add(hormiga.getName()); // Queda reflejado que está dentro del almacen
			this.cambioRelease();
			Thread.sleep((long) (((Math.random()*2)+2)*1000)); // Tiempo que tarda en depositarlo
			this.semUnidadesAlmacenExclusion.acquire(); // Exclusion
			this.unidadesComidaAlmacen+=5; // Deposita la comida en el almacén
			this.semUnidadesAlmacenExclusion.release(); // Exclusion
			this.cambioRelease();
			this.addLog(hormiga, ", ha depositado la comida y ha salido del almacén.");
		} catch(InterruptedException ie) {}
		finally {
			this.semAlmacenComida.release();
			this.semUnidadesAlmacenVacio.release(); // Sincronizacion
			this.hAlmacenComida.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
		}
	}
	
	public void entrarAlmacenComidaConsumir(HormigaObrera hormiga) {
		try {
			this.semUnidadesAlmacenVacio.acquire(); // Sincronización
			this.semAlmacenComida.acquire(); // Entra en el almacen de comida
			// Está la hormiga en el tunel
			this.addLog(hormiga, ", ha entrado al almacén de comida a consumir.");
			this.hAlmacenComida.add(hormiga.getName()); // Queda reflejado que está dentro del almacen
			this.cambioRelease();
			Thread.sleep((long) (((Math.random()*1)+1)*1000)); // Tiempo que tarda en depositarlo
			this.semUnidadesAlmacenExclusion.acquire(); // Exclusion
			this.unidadesComidaAlmacen-=5;
			this.semUnidadesAlmacenExclusion.release();
			this.cambioRelease();
			this.addLog(hormiga, ", ha recogido la comida y ha salido del almacén.");
		} catch(InterruptedException ie) {}
		finally {
			this.semAlmacenComida.release();
			this.semUnidadesAlmacenLleno.release();
			this.hAlmacenComida.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
		}
	}
	
	public void transicionZonaComer(HormigaObrera hormiga) {
		try {
			this.addLog(hormiga, ", está haciendo el camino para la zona para comer.");
			this.hLlevandoZonaComer.add(hormiga.getName()); // Queda reflejado que está dentro del almacen
			this.cambioRelease();
			Thread.sleep((long) (((Math.random()*2)+1)*1000)); // Tiempo que tarda en depositarlo
			this.addLog(hormiga, ", ha llegado a la zona comer.");
		} catch(InterruptedException ie) {}
		finally {
			this.hLlevandoZonaComer.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
		}
	}
	
	public void entrarZonaComerDepositar(HormigaObrera hormiga, int unidadesADepositar) {
		try {
			this.addLog(hormiga, ", ha entrado a la zona comer a depositar.");
			this.hZonaComer.add(hormiga.getName()); // Queda reflejado que está dentro
			this.cambioRelease();
			Thread.sleep((long) (((Math.random())+1)*1000)); // Tiempo que tarda en depositarlo
			this.unidadesComidaZonaComer.addAndGet(unidadesADepositar); // Deposita la comida en el almacén
			this.cambioRelease();
			this.addLog(hormiga, ", ha depositado la comida y ha salido de la zona comer.");
			this.semUnidadesZonaComer.release();
		} catch(InterruptedException ie) {}
		finally {
			this.hZonaComer.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
		}
	}
	// Métodos hormigas soldado
	public void entrarZonaInstruccion(HormigaSoldado hormiga) {
		try {
			this.addLog(hormiga, ", ha entrado a la zona instruccion a entrenar.");
			this.hZonaInstruccion.add(hormiga.getName()); // Queda reflejado que está dentro
			this.cambioRelease();
			Thread.sleep((long) (((Math.random()*6)+2)*1000)); // Tiempo que tarda en entrenar
			this.addLog(hormiga, ", ha terminado de entrenar y ha salido de la zona de instrucción.");
			this.hZonaInstruccion.remove(hormiga.getNombreHormiga());
		} catch(InterruptedException ie) {
			this.hZonaInstruccion.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
			this.lucharInsectoInvasor(hormiga);
		}
		finally {
			this.cambioRelease();
		}
	}
	public void lucharInsectoInvasor(HormigaSoldado hormiga) {
		this.pasarTunelSalida(hormiga);
		this.hRepeliendoInsecto.add(hormiga.getNombreHormiga());
		this.cambioRelease();
		try {
			this.addLog(hormiga, ", se está enfrentando al insecto invasor."); // FOR THE COLONY
			Thread.sleep(20*1000); // Tiempo que está luchando contra el insecto.
			this.addLog(hormiga, ", ha terminado de enfrentarse al insecto invasor.");
		} catch (InterruptedException e) {} 
		finally {
			this.hRepeliendoInsecto.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
			this.pasarTunelEntrada(hormiga);
		}
		
	}
	// Métodos hormigas cria
	public void entrarZonaRefugio(HormigaCria hormiga) {
		this.hRefugio.add(hormiga.getNombreHormiga());
		this.cambioRelease();
		try {
			this.addLog(hormiga, ", ha entrado al refugio (sólo hormigas cria)."); // Entra en el refugio
			this.semLuchandoInsecto.acquire();
			this.addLog(hormiga, ", ha salido del refugio (sólo hormigas cria).");
		} catch (InterruptedException e) {} 
		finally {
			this.hRefugio.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
		}
	}
	
	// Métodos generales
	public void entrarZonaComerConsumir(Hormiga hormiga, int tiempoComer) {
		try {
			this.semUnidadesZonaComer.acquire(); // Sincronización, no deja entrar a no ser que haya unidades
			this.addLog(hormiga, ", ha entrado a la zona comer a comer.");
			this.hZonaComer.add(hormiga.getNombreHormiga()); // Queda reflejado que está dentro
			this.unidadesComidaZonaComer.decrementAndGet();
			this.cambioRelease();
			Thread.sleep(tiempoComer*1000); // Tiempo que tarda en comer
			this.addLog(hormiga, ", ha comido y ha salido de la zona comer.");
		} catch(InterruptedException ie) {
			this.hZonaComer.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
			if(hormiga.getIdType() == "HS") { // Es una hormiga soldado a luchar
				this.lucharInsectoInvasor((HormigaSoldado) hormiga);
			}
			if(hormiga.getIdType() == "HC") { // Es una hormiga cria al refugio
				this.entrarZonaRefugio((HormigaCria) hormiga);
			}
		}
		finally {
			this.hZonaComer.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
		}
	}
	
	public void entrarZonaComerConsumir(Hormiga hormiga) {
		this.entrarZonaComerConsumir(hormiga, 3);
	}
	
	public void entrarZonaDescanso(Hormiga hormiga, int tiempoDescansando) {
		try {
			this.addLog(hormiga, ", ha entrado a la zona de descanso a mimir.");
			this.hZonaDescanso.add(hormiga.getNombreHormiga()); // Queda reflejado que está dentro
			this.cambioRelease();
			Thread.sleep(tiempoDescansando * 1000); // Tiempo que tarda en comer
			this.addLog(hormiga, ", ha descansado y ha salido de la zona de descanso.");
		} catch(InterruptedException ie) {
			this.hZonaDescanso.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
			if(hormiga.getIdType() == "HS") { // Es una hormiga soldado a luchar
				this.lucharInsectoInvasor((HormigaSoldado) hormiga);
			}
			if(hormiga.getIdType() == "HC") { // Es una hormiga cria al refugio
				this.entrarZonaRefugio((HormigaCria) hormiga);
			}
		}
		finally {
			this.hZonaDescanso.remove(hormiga.getNombreHormiga());
			this.cambioRelease();
		}
	}

	// Override de la interfaz Runnable
	@Override
	public void run() {
		// Me creo el hilo del log
		new Thread(this.log).start();

		try {
			new HormigaObrera(this).start();
			Thread.sleep((long) (((Math.random()*2.7)+0.8)*1000));
		} catch (LoggingException | InterruptedException e) {
			e.printStackTrace();
		}
		try {
			for(int i =0; i < 9999; ) {
				
				if(this.pararEjecucion.get()) { // Espera activa :(
					Thread.sleep(1000);
				}
				else {
					// Cada 3 hormigas obreras se crerarán una soldado y una cria
					if(i%4 == 3) {
						new HormigaSoldado(this).start();
					}
					if(i%4 == 2) {
						new HormigaCria(this).start();
					}
					else {
						new HormigaObrera(this).start();
					}
					Thread.sleep((long) (((Math.random()*2.7)+0.8)*1000));
					i++;
				}
			}
		} catch (LoggingException | InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
