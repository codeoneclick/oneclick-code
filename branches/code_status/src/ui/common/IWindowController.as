package ui.common 
{
	import common.mvc.IController;
	import common.mvc.IView;
	import flash.display.DisplayObjectContainer;
	/**
	 * ...
	 * @author sergey.sergeev.code.oneclick
	 */
	public class IWindowController extends IController
	{
		
		public function IWindowController(_container:DisplayObjectContainer, _view:IView) 
		{
			super(_container, _view);
			init();
		}
		
		private function init():void
		{
			
		}
		
	}

}