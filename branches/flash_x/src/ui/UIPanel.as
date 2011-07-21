package ui 
{
	import core.Global;
	import fl.containers.ScrollPane;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class UIPanel 
	{
		protected var m_plane:ScrollPane = new ScrollPane();
		protected var m_name:String = "";
		
		public function UIPanel() 
		{
			m_plane.height = Global.setting.windowHeight - UISetting.k_PANEL_OFFSET;
			m_plane.width = UISetting.k_PANEL_WIDTH;
			
			m_plane.x = Global.setting.windowWidth - m_plane.width;
			m_plane.y = UISetting.k_PANEL_OFFSET;
			
			Global.uiContainer.addChild(m_plane);
		}
		
		public function set visible(_value:Boolean):void
		{
			m_plane.visible = _value;
		}
		
		public function set name(_value:String):void
		{
			m_name = _value;
		}
		
		public function get name():String
		{
			return m_name;
		}
		
	}

}