package parte2;

import java.awt.Color;
import java.awt.Font;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import parte2.interfaces.VistaClienteRMI;

import java.awt.event.ActionListener;
import java.rmi.RemoteException;
import java.awt.event.ActionEvent;

public class GUICliente {
	
	private VistaClienteRMI controlador;	// Usado para la logica MVC

	private JFrame frmAplicacinHormigas;
	private JButton btnGenerarAmenazaInsecto;
	private JTextField txtfHormigasObrerasExterior;
	private JTextField txtfHormigasObrerasInterior;
	private JTextField txtfHormigasSoldadoInsruccion;
	private JTextField txtfHormigasSoldadoInvasion;
	private JTextField txtfHormigasCriaZonaComer;
	private JTextField txtfHormigasCriaRefugio;
	
	// Getters and Setters
	public JFrame getFrmAplicacinHormigas() {
		return frmAplicacinHormigas;
	}

	public void setFrmAplicacinHormigas(JFrame frmAplicacinHormigas) {
		this.frmAplicacinHormigas = frmAplicacinHormigas;
	}

	public JTextField getTxtfHormigasObrerasExterior() {
		return txtfHormigasObrerasExterior;
	}

	public void setTxtfHormigasObrerasExterior(JTextField txtfHormigasObrerasExterior) {
		this.txtfHormigasObrerasExterior = txtfHormigasObrerasExterior;
	}

	public JTextField getTxtfHormigasObrerasInterior() {
		return txtfHormigasObrerasInterior;
	}

	public void setTxtfHormigasObrerasInterior(JTextField txtfHormigasObrerasInterior) {
		this.txtfHormigasObrerasInterior = txtfHormigasObrerasInterior;
	}

	public JTextField getTxtfHormigasSoldadoInsruccion() {
		return txtfHormigasSoldadoInsruccion;
	}

	public void setTxtfHormigasSoldadoInsruccion(JTextField txtfHormigasSoldadoInsruccion) {
		this.txtfHormigasSoldadoInsruccion = txtfHormigasSoldadoInsruccion;
	}

	public JTextField getTxtfHormigasSoldadoInvasion() {
		return txtfHormigasSoldadoInvasion;
	}

	public void setTxtfHormigasSoldadoInvasion(JTextField txtfHormigasSoldadoInvasion) {
		this.txtfHormigasSoldadoInvasion = txtfHormigasSoldadoInvasion;
	}

	public JTextField getTxtfHormigasCriaZonaComer() {
		return txtfHormigasCriaZonaComer;
	}

	public void setTxtfHormigasCriaZonaComer(JTextField txtfHormigasCriaZonaComer) {
		this.txtfHormigasCriaZonaComer = txtfHormigasCriaZonaComer;
	}

	public JTextField getTxtfHormigasCriaRefugio() {
		return txtfHormigasCriaRefugio;
	}

	public void setTxtfHormigasCriaRefugio(JTextField txtfHormigasCriaRefugio) {
		this.txtfHormigasCriaRefugio = txtfHormigasCriaRefugio;
	}
	
	public JButton getBtnGenerarAmenazaInsecto() {
		return btnGenerarAmenazaInsecto;
	}

	public void setBtnGenerarAmenazaInsecto(JButton btnGenerarAmenazaInsecto) {
		this.btnGenerarAmenazaInsecto = btnGenerarAmenazaInsecto;
	}

	
	/**
	 * Launch the application.
	 */
	/*public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					GUI window = new GUI();
					window.frmAplicacinHormigas.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}*/

	/**
	 * Create the application.
	 */
	public GUICliente(VistaClienteRMI controlador) {
		// Es obligatorio configurar el controlador antes de crear los objetos de la clase
		this.controlador = controlador; 
		initialize();
		crearHiloCambios(this);
	}
	
	/*public GUICliente() {
		initialize();
	}*/

	protected void crearHiloCambios(GUICliente gui) {
		new Thread(Thread.currentThread().getThreadGroup(),
				new Runnable() {
					public void run() {
						try {
							while(true) {
								try {
									gui.controlador.cambioAdquireRMI();
								} catch (InterruptedException ie) {}
								gui.getTxtfHormigasObrerasExterior().setText(
										Long.toString(
											gui.controlador.gethFueraColoniaRMI().stream()
											.filter(elemento -> elemento.contains("HO"))
											.count()
										));
								gui.getTxtfHormigasObrerasInterior().setText(
										Long.toString(
											gui.controlador.gethDentroColoniaRMI().stream()
											.filter(elemento -> elemento.contains("HO"))
											.count()
										));	
								gui.getTxtfHormigasSoldadoInsruccion().setText(
										Long.toString(
											gui.controlador.gethZonaInstruccionRMI().stream()
											.count()
										));
								gui.getTxtfHormigasSoldadoInvasion().setText(
										Long.toString(
											gui.controlador.gethRepeliendoInsectoRMI().stream()
											.count()
										));
								gui.getTxtfHormigasCriaZonaComer().setText(
										Long.toString(
											gui.controlador.gethZonaComerRMI().stream()
											.filter(elemento -> elemento.contains("HC"))
											.count()
										));
								gui.getTxtfHormigasCriaRefugio().setText(
										Long.toString(
											gui.controlador.gethRefugioRMI().stream()
											.count()
										));
							}
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				},
				"HiloEventoControlador"
			).start();
	}
	

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frmAplicacinHormigas = new JFrame();
		frmAplicacinHormigas.setResizable(false);
		frmAplicacinHormigas.setTitle("Aplicación Hormigas Cliente");
		frmAplicacinHormigas.setBounds(100, 100, 715, 494);
		frmAplicacinHormigas.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmAplicacinHormigas.getContentPane().setLayout(null);
		
		JLabel lblHormigasObrerasExterior = new JLabel("Número de hormigas obreras en el exterior de la colonia:");
		lblHormigasObrerasExterior.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblHormigasObrerasExterior.setBounds(126, 79, 353, 28);
		frmAplicacinHormigas.getContentPane().add(lblHormigasObrerasExterior);
		
		JLabel lblHormigasObrerasInterior = new JLabel("Número de hormigas obreras en el interior de la colonia:");
		lblHormigasObrerasInterior.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblHormigasObrerasInterior.setBounds(126, 132, 353, 14);
		frmAplicacinHormigas.getContentPane().add(lblHormigasObrerasInterior);
		
		btnGenerarAmenazaInsecto = new JButton("Generar Amenaza Insecto Invasor");
		btnGenerarAmenazaInsecto.setFont(new Font("Tahoma", Font.PLAIN, 18));
		btnGenerarAmenazaInsecto.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					controlador.generarInsectoInvasorRMI();
				} catch (RemoteException e1) {
					e1.printStackTrace();
				}
			}
		});
		btnGenerarAmenazaInsecto.setBounds(170, 349, 389, 41);
		frmAplicacinHormigas.getContentPane().add(btnGenerarAmenazaInsecto);
		
		txtfHormigasObrerasExterior = new JTextField();
		txtfHormigasObrerasExterior.setForeground(Color.BLACK);
		txtfHormigasObrerasExterior.setEditable(false);
		txtfHormigasObrerasExterior.setColumns(10);
		txtfHormigasObrerasExterior.setBounds(520, 82, 89, 26);
		frmAplicacinHormigas.getContentPane().add(txtfHormigasObrerasExterior);
		
		txtfHormigasObrerasInterior = new JTextField();
		txtfHormigasObrerasInterior.setForeground(Color.BLACK);
		txtfHormigasObrerasInterior.setEditable(false);
		txtfHormigasObrerasInterior.setColumns(10);
		txtfHormigasObrerasInterior.setBounds(520, 128, 89, 26);
		frmAplicacinHormigas.getContentPane().add(txtfHormigasObrerasInterior);
		
		JLabel lblHormigasSoldadoInstruccion = new JLabel("Número de hormigas soldado haciendo instrucción:");
		lblHormigasSoldadoInstruccion.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblHormigasSoldadoInstruccion.setBounds(126, 165, 353, 28);
		frmAplicacinHormigas.getContentPane().add(lblHormigasSoldadoInstruccion);
		
		txtfHormigasSoldadoInsruccion = new JTextField();
		txtfHormigasSoldadoInsruccion.setForeground(Color.BLACK);
		txtfHormigasSoldadoInsruccion.setEditable(false);
		txtfHormigasSoldadoInsruccion.setColumns(10);
		txtfHormigasSoldadoInsruccion.setBounds(520, 168, 89, 26);
		frmAplicacinHormigas.getContentPane().add(txtfHormigasSoldadoInsruccion);
		
		JLabel lblHormigasSoldadoInvasion = new JLabel("Número de hormigas soldado repeliendo una invasión:");
		lblHormigasSoldadoInvasion.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblHormigasSoldadoInvasion.setBounds(126, 204, 353, 28);
		frmAplicacinHormigas.getContentPane().add(lblHormigasSoldadoInvasion);
		
		txtfHormigasSoldadoInvasion = new JTextField();
		txtfHormigasSoldadoInvasion.setForeground(Color.BLACK);
		txtfHormigasSoldadoInvasion.setEditable(false);
		txtfHormigasSoldadoInvasion.setColumns(10);
		txtfHormigasSoldadoInvasion.setBounds(520, 207, 89, 26);
		frmAplicacinHormigas.getContentPane().add(txtfHormigasSoldadoInvasion);
		
		JLabel lblHormigasCriaZonaComer = new JLabel("Número de hormigas crías en la ZONA PARA COMER:");
		lblHormigasCriaZonaComer.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblHormigasCriaZonaComer.setBounds(126, 243, 353, 28);
		frmAplicacinHormigas.getContentPane().add(lblHormigasCriaZonaComer);
		
		txtfHormigasCriaZonaComer = new JTextField();
		txtfHormigasCriaZonaComer.setForeground(Color.BLACK);
		txtfHormigasCriaZonaComer.setEditable(false);
		txtfHormigasCriaZonaComer.setColumns(10);
		txtfHormigasCriaZonaComer.setBounds(520, 246, 89, 26);
		frmAplicacinHormigas.getContentPane().add(txtfHormigasCriaZonaComer);
		
		JLabel lblHormigasCriaRefugio = new JLabel("Número de hormigas crías en el REFUGIO:");
		lblHormigasCriaRefugio.setFont(new Font("Tahoma", Font.PLAIN, 14));
		lblHormigasCriaRefugio.setBounds(126, 282, 353, 28);
		frmAplicacinHormigas.getContentPane().add(lblHormigasCriaRefugio);
		
		txtfHormigasCriaRefugio = new JTextField();
		txtfHormigasCriaRefugio.setForeground(Color.BLACK);
		txtfHormigasCriaRefugio.setEditable(false);
		txtfHormigasCriaRefugio.setColumns(10);
		txtfHormigasCriaRefugio.setBounds(520, 285, 89, 26);
		frmAplicacinHormigas.getContentPane().add(txtfHormigasCriaRefugio);
	}
}
