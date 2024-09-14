package parte1;

import java.awt.Color;
import java.awt.Font;
import java.awt.TextArea;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

import parte1.interfaces.VistaHormigaGUI;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class GUI {
	
	private VistaHormigaGUI controlador;	// Usado para la logica MVC

	private JFrame frmAplicacinHormigas;
	private JTextField txtfHormigasBuscandoComida;
	private JTextField txtfHormigasAlmacenComida;
	private JTextField txtfHomigasLlevandoZonaComer;
	private JTextField txtfHomigasInstruccion;
	private JTextField txtfHomigasDescansando;
	private JTextField txtfUnidadesAlmacen;
	private JTextField txtfUnidadesZonaComer;
	// Adaptado
	private TextArea txtaHormigasRepeliendoInsecto;
	private TextArea txtaZonaParaComer;
	private TextArea txtaRefugio;
	private JButton btnGenerarAmenazaInsecto;
	
	// Getters and Setters
	public JFrame getFrmAplicacinHormigas() {
		return frmAplicacinHormigas;
	}

	public void setFrmAplicacinHormigas(JFrame frmAplicacinHormigas) {
		this.frmAplicacinHormigas = frmAplicacinHormigas;
	}

	public JTextField getTxtfHormigasBuscandoComida() {
		return txtfHormigasBuscandoComida;
	}

	public void setTxtfHormigasBuscandoComida(JTextField txtfHormigasBuscandoComida) {
		this.txtfHormigasBuscandoComida = txtfHormigasBuscandoComida;
	}

	public JTextField getTxtfHormigasAlmacenComida() {
		return txtfHormigasAlmacenComida;
	}

	public void setTxtfHormigasAlmacenComida(JTextField txtfHormigasAlmacenComida) {
		this.txtfHormigasAlmacenComida = txtfHormigasAlmacenComida;
	}

	public JTextField getTxtfHomigasLlevandoZonaComer() {
		return txtfHomigasLlevandoZonaComer;
	}

	public void setTxtfHomigasLlevandoZonaComer(JTextField txtfHomigasLlevandoZonaComer) {
		this.txtfHomigasLlevandoZonaComer = txtfHomigasLlevandoZonaComer;
	}

	public JTextField getTxtfHomigasInstruccion() {
		return txtfHomigasInstruccion;
	}

	public void setTxtfHomigasInstruccion(JTextField txtfHomigasInstruccion) {
		this.txtfHomigasInstruccion = txtfHomigasInstruccion;
	}

	public JTextField getTxtfHomigasDescansando() {
		return txtfHomigasDescansando;
	}

	public void setTxtfHomigasDescansando(JTextField txtfHomigasDescansando) {
		this.txtfHomigasDescansando = txtfHomigasDescansando;
	}

	public JTextField getTxtfUnidadesAlmacen() {
		return txtfUnidadesAlmacen;
	}

	public void setTxtfUnidadesAlmacen(JTextField txtfUnidadesAlmacen) {
		this.txtfUnidadesAlmacen = txtfUnidadesAlmacen;
	}

	public JTextField getTxtfUnidadesZonaComer() {
		return txtfUnidadesZonaComer;
	}

	public void setTxtfUnidadesZonaComer(JTextField txtfUnidadesZonaComer) {
		this.txtfUnidadesZonaComer = txtfUnidadesZonaComer;
	}

	public TextArea getTxtaHormigasRepeliendoInsecto() {
		return txtaHormigasRepeliendoInsecto;
	}

	public void setTxtaHormigasRepeliendoInsecto(TextArea txtaHormigasRepeliendoInsecto) {
		this.txtaHormigasRepeliendoInsecto = txtaHormigasRepeliendoInsecto;
	}

	public TextArea getTxtaZonaParaComer() {
		return txtaZonaParaComer;
	}

	public void setTxtaZonaParaComer(TextArea txtaZonaParaComer) {
		this.txtaZonaParaComer = txtaZonaParaComer;
	}

	public TextArea getTxtaRefugio() {
		return txtaRefugio;
	}

	public void setTxtaRefugio(TextArea txtaRefugio) {
		this.txtaRefugio = txtaRefugio;
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
	public GUI(VistaHormigaGUI controlador) {
		// Es obligatorio configurar el controlador antes de crear los objetos de la clase
		this.controlador = controlador; 
		initialize();
		crearHiloCambios(this);
	}

	protected void crearHiloCambios(GUI gui) {
		new Thread(Thread.currentThread().getThreadGroup(),
				new Runnable() {
					public void run() {
						try {
							while(true) {
								try {
									gui.controlador.cambioAdquire();
								} catch (InterruptedException ie) {}
								gui.getTxtfUnidadesAlmacen().setText(Integer.toString(gui.controlador.getUnidadesComidaAlmacen()));
								gui.getTxtfUnidadesZonaComer().setText(gui.controlador.getUnidadesComidaZonaComer().toString());	
								gui.getTxtfHormigasBuscandoComida().setText(String.join(",", gui.controlador.gethBuscandoComida()));
								gui.getTxtaHormigasRepeliendoInsecto().setText(String.join(",", gui.controlador.gethRepeliendoInsecto()));
								gui.getTxtfHormigasAlmacenComida().setText(String.join(",", gui.controlador.gethAlmacenComida()));
								gui.getTxtfHomigasLlevandoZonaComer().setText(String.join(",", gui.controlador.gethLlevandoZonaComer()));
								gui.getTxtfHomigasInstruccion().setText(String.join(",", gui.controlador.gethZonaInstruccion()));
								gui.getTxtfHomigasDescansando().setText(String.join(",", gui.controlador.gethZonaDescanso()));
								gui.getTxtaZonaParaComer().setText(String.join(",", gui.controlador.gethZonaComer()));
								gui.getTxtaRefugio().setText(String.join(",", gui.controlador.gethRefugio()));
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
		frmAplicacinHormigas.setTitle("Aplicación Hormigas Servidor");
		frmAplicacinHormigas.setBounds(100, 100, 941, 705);
		frmAplicacinHormigas.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmAplicacinHormigas.getContentPane().setLayout(null);
		
		JLabel lblExteriordelaColonia = new JLabel("Exterior de la colonia:");
		lblExteriordelaColonia.setBounds(7, 7, 251, 17);
		lblExteriordelaColonia.setFont(new Font("Tahoma", Font.BOLD, 14));
		frmAplicacinHormigas.getContentPane().add(lblExteriordelaColonia);
		
		JLabel lblHormigasBuscandoComida = new JLabel("Hormigas buscando comida:\r\n");
		lblHormigasBuscandoComida.setBounds(7, 31, 309, 14);
		lblHormigasBuscandoComida.setLabelFor(lblExteriordelaColonia);
		frmAplicacinHormigas.getContentPane().add(lblHormigasBuscandoComida);
		
		txtfHormigasBuscandoComida = new JTextField();
		txtfHormigasBuscandoComida.setForeground(new Color(0, 0, 0));
		txtfHormigasBuscandoComida.setEditable(false);
		txtfHormigasBuscandoComida.setBounds(326, 31, 503, 20);
		frmAplicacinHormigas.getContentPane().add(txtfHormigasBuscandoComida);
		txtfHormigasBuscandoComida.setColumns(10);
		
		JLabel lblHormigasRepeliendoInsecto = new JLabel("Hormigas repeliendo un insecto invasor:");
		lblHormigasRepeliendoInsecto.setBounds(7, 84, 313, 14);
		frmAplicacinHormigas.getContentPane().add(lblHormigasRepeliendoInsecto);
		
		txtaHormigasRepeliendoInsecto = new TextArea();
		txtaHormigasRepeliendoInsecto.setEditable(false);
		txtaHormigasRepeliendoInsecto.setForeground(new Color(0, 0, 0));
		txtaHormigasRepeliendoInsecto.setBounds(326, 87, 503, 160);
		frmAplicacinHormigas.getContentPane().add(txtaHormigasRepeliendoInsecto);
		
		JLabel lblInteriordelaColonia = new JLabel("Interior de la colonia:");
		lblInteriordelaColonia.setBounds(7, 245, 251, 17);
		lblInteriordelaColonia.setFont(new Font("Tahoma", Font.BOLD, 14));
		frmAplicacinHormigas.getContentPane().add(lblInteriordelaColonia);
		
		JLabel lblHormigasAlmacenComida = new JLabel("Hormigas en el ALMACÉN DE COMIDA:");
		lblHormigasAlmacenComida.setBounds(7, 269, 313, 14);
		frmAplicacinHormigas.getContentPane().add(lblHormigasAlmacenComida);
		
		txtfHormigasAlmacenComida = new JTextField();
		txtfHormigasAlmacenComida.setEditable(false);
		txtfHormigasAlmacenComida.setBounds(326, 269, 503, 20);
		frmAplicacinHormigas.getContentPane().add(txtfHormigasAlmacenComida);
		txtfHormigasAlmacenComida.setColumns(10);
		
		JLabel lblHomigasLlevandoZonaComer = new JLabel("Hormigas llevando comida a la ZONA PARA COMER:");
		lblHomigasLlevandoZonaComer.setBounds(7, 293, 313, 14);
		frmAplicacinHormigas.getContentPane().add(lblHomigasLlevandoZonaComer);
		
		txtfHomigasLlevandoZonaComer = new JTextField();
		txtfHomigasLlevandoZonaComer.setEditable(false);
		txtfHomigasLlevandoZonaComer.setBounds(326, 293, 503, 20);
		frmAplicacinHormigas.getContentPane().add(txtfHomigasLlevandoZonaComer);
		txtfHomigasLlevandoZonaComer.setColumns(10);
		
		JLabel lblHomigasInstruccion = new JLabel("Hormigas haciendo INSTRUCCIÓN");
		lblHomigasInstruccion.setBounds(7, 317, 309, 14);
		frmAplicacinHormigas.getContentPane().add(lblHomigasInstruccion);
		
		txtfHomigasInstruccion = new JTextField();
		txtfHomigasInstruccion.setEditable(false);
		txtfHomigasInstruccion.setBounds(326, 317, 503, 17);
		frmAplicacinHormigas.getContentPane().add(txtfHomigasInstruccion);
		txtfHomigasInstruccion.setColumns(10);
		
		JLabel lblHormigasDescansando = new JLabel("Hormigas descansando:");
		lblHormigasDescansando.setBounds(7, 338, 309, 14);
		frmAplicacinHormigas.getContentPane().add(lblHormigasDescansando);
		
		txtfHomigasDescansando = new JTextField();
		txtfHomigasDescansando.setEditable(false);
		txtfHomigasDescansando.setBounds(326, 338, 236, 20);
		frmAplicacinHormigas.getContentPane().add(txtfHomigasDescansando);
		txtfHomigasDescansando.setColumns(10);
		
		JLabel lblUnidadesAlmacen = new JLabel("Unidades de Comida (ALMACÉN)");
		lblUnidadesAlmacen.setHorizontalAlignment(SwingConstants.RIGHT);
		lblUnidadesAlmacen.setBounds(572, 341, 267, 14);
		frmAplicacinHormigas.getContentPane().add(lblUnidadesAlmacen);
		
		txtfUnidadesAlmacen = new JTextField();
		txtfUnidadesAlmacen.setEditable(false);
		txtfUnidadesAlmacen.setBounds(849, 338, 42, 20);
		frmAplicacinHormigas.getContentPane().add(txtfUnidadesAlmacen);
		txtfUnidadesAlmacen.setColumns(10);
		
		JLabel lblUnidadesZonaComer = new JLabel("Unidades de Comida (ZONA PARA COMER)");
		lblUnidadesZonaComer.setHorizontalAlignment(SwingConstants.RIGHT);
		lblUnidadesZonaComer.setBounds(572, 373, 272, 14);
		frmAplicacinHormigas.getContentPane().add(lblUnidadesZonaComer);
		
		txtfUnidadesZonaComer = new JTextField();
		txtfUnidadesZonaComer.setEditable(false);
		txtfUnidadesZonaComer.setColumns(10);
		txtfUnidadesZonaComer.setBounds(849, 370, 42, 20);
		frmAplicacinHormigas.getContentPane().add(txtfUnidadesZonaComer);
		
		JLabel lblZonaParaComer = new JLabel("ZONA PARA COMER:");
		lblZonaParaComer.setBounds(7, 419, 313, 14);
		frmAplicacinHormigas.getContentPane().add(lblZonaParaComer);
		
		txtaZonaParaComer = new TextArea();
		txtaZonaParaComer.setEditable(false);
		txtaZonaParaComer.setBounds(326, 422, 503, 84);
		frmAplicacinHormigas.getContentPane().add(txtaZonaParaComer);
		
		JLabel lblRefugio = new JLabel("REFUGIO:");
		lblRefugio.setBounds(7, 509, 309, 14);
		frmAplicacinHormigas.getContentPane().add(lblRefugio);
		
		txtaRefugio = new TextArea();
		txtaRefugio.setEditable(false);
		txtaRefugio.setBounds(326, 512, 503, 84);
		frmAplicacinHormigas.getContentPane().add(txtaRefugio);
		
		JButton btnPausar = new JButton("Pausar");
		btnPausar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controlador.pararEjecucion();
				btnGenerarAmenazaInsecto.setEnabled(false);
			}
		});
		btnPausar.setBounds(32, 618, 89, 23);
		frmAplicacinHormigas.getContentPane().add(btnPausar);
		
		JButton btnReanudar = new JButton("Reanudar");
		btnReanudar.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controlador.continuarEjecucion();
				btnGenerarAmenazaInsecto.setEnabled(true);
			}
		});
		btnReanudar.setBounds(169, 618, 89, 23);
		frmAplicacinHormigas.getContentPane().add(btnReanudar);
		
		btnGenerarAmenazaInsecto = new JButton("Generar Amenaza Insecto Invasor");
		btnGenerarAmenazaInsecto.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				controlador.generarInsectoInvasor();
			}
		});
		btnGenerarAmenazaInsecto.setBounds(572, 618, 257, 23);
		frmAplicacinHormigas.getContentPane().add(btnGenerarAmenazaInsecto);
	}
}
