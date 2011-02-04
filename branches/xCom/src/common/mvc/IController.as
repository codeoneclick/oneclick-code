package common.mvc 
{
	import flash.display.DisplayObjectContainer;
	/**
	 * ...
	 * @author ...
	 */
	public class IController 
	{
		protected var m_container:DisplayObjectContainer = null;
		protected var m_model:IModel = null;
		protected var m_viewer:IViewer= null;
		
		public function IController(_container:DisplayObjectContainer, _viewer:IViewer, _model:IModel) 
		{
			m_container = _container;
			m_model = _model;
			m_viewer = _viewer;
			init();
		}
		
		private function init():void
		{
			m_container.addChild(m_viewer);
		}
		
	}

}