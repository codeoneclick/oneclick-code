package ui 
{
	import ui.common.IWindowView;
	/**
	 * ...
	 * @author sergey.sergeev.code.oneclick
	 */
	public class UILoginWindowView extends IWindowView
	{
		[Embed(source="../../res/login_window.swf", symbol="login_window")]
		private static var m_window:Class;
		
		public function UILoginWindowView() 
		{
			addChild(new m_window);
		}
		
	}

}