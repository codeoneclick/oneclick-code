package common.mvc 
{
	import flash.display.DisplayObjectContainer;
	import flash.events.EventDispatcher;
	/**
	 * ...
	 * @author sergey.sergeev.code.oneclick
	 */
	public class IController extends EventDispatcher
	{
		private var m_container:DisplayObjectContainer = null;
		private var m_view:IView = null;
		
		public function IController(_container:DisplayObjectContainer, _view:IView) 
		{
			super(m_view);
			m_container = _container;
			m_view = _view;
			init();
		}
		
		private function init():void
		{
			m_container.addChild(m_view);
		}
		
	}

}