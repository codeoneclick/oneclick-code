package core 
{
	import common.resource.ResourceController;
	import editor.EditorController;
	import flash.display.DisplayObjectContainer;
	import flash.display.Stage;
	import game.SceneController;
	import ui.UICameraControls;
	import ui.UIController;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Global 
	{
		
		private static var m_stage:Stage = null;
		
		private static var m_inGameContainer:DisplayObjectContainer = null;
		
		private static var m_uiContainer:DisplayObjectContainer = null;
		
		private static var m_backContainer:DisplayObjectContainer = null;
		
		private static var m_resourceController:ResourceController = null;
		
		private static var m_sceneController:SceneController = null;
		
		private static var m_uiController:UIController = null;
		
		private static var m_input:Input = null;
		
		private static var m_camera:Camera = null;
		
		private static var m_cameraControls:UICameraControls = null;
		
		private static var m_setting:Setting = new Setting();
		
		private static var m_editorController:EditorController = null;
		
		private static var m_mouseIcon:GameMouseIcon = null;
		
		public function Global() 
		{
			
		}
		
		public static function set stage(_value:Stage):void
		{
			m_stage = _value;
		}
		
		public static function get stage():Stage
		{
			return m_stage;
		}
		
		public static function set inGameContainer(_value:DisplayObjectContainer):void
		{
			m_inGameContainer = _value;
		}
		
		public static function get inGameContainer():DisplayObjectContainer
		{
			return m_inGameContainer;
		}
		
		public static function set uiContainer(_value:DisplayObjectContainer):void
		{
			m_uiContainer = _value;
		}
		
		public static function get uiContainer():DisplayObjectContainer
		{
			return m_uiContainer;
		}
		
		public static function get resourceController():ResourceController
		{
			if (m_resourceController == null)
			{
				m_resourceController = new ResourceController();
			}
			
			return m_resourceController;
		}
		
		public static function set sceneController(_value:SceneController):void
		{
			m_sceneController = _value;
		}
		
		public static function get sceneController():SceneController
		{
			return m_sceneController;
		}
		
		public static function set uiController(_value:UIController):void
		{
			m_uiController = _value;
		}
		
		public static function get uiController():UIController
		{
			return m_uiController;
		}
		
		public static function set input(_value:Input):void
		{
			m_input = _value;
		}
		
		public static function get input():Input
		{
			return m_input;
		}
		
		public static function set camera(_value:Camera):void
		{
			m_camera = _value;
		}
		
		public static function get camera():Camera
		{
			return m_camera;
		}
		
		public static function set cameraControls(_value:UICameraControls):void
		{
			m_cameraControls = _value;
		}
		
		public static function get cameraControls():UICameraControls
		{
			return m_cameraControls;
		}
		
		public static function get setting():Setting
		{
			return m_setting;
		}
		
		public static function set editorController(_value:EditorController):void
		{
			m_editorController = _value;
		}
		
		public static function get editorController():EditorController
		{
			return m_editorController;
		}
		
		public static function get backContainer():DisplayObjectContainer
		{
			return m_backContainer;
		}
		
		public static function set backContainer(_value:DisplayObjectContainer):void
		{
			m_backContainer = _value;
		}
		
		public static function set mouseIcon(icon:GameMouseIcon):void
		{
			m_mouseIcon = icon;
		}
		
		public static function get mouseIcon():GameMouseIcon
		{
			return m_mouseIcon;
		}
		
	}

}