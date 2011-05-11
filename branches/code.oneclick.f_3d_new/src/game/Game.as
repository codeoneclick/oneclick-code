package game 
{
	import game.core.Core;
	import game.enviroment.Level;
	import game.ui.MainMenu;
	/**
	 * ...
	 * @author ...
	 */
	public class Game 
	{
		private var m_level:Level = null;
		private var m_mainMenu:MainMenu = null;
		
		public function Game() 
		{
			init();
		}
		
		private function init():void
		{
			m_level = new Level();
			m_mainMenu = new MainMenu("main_menu", Core.displayContainer, m_level.onUIEventCallback);
		}
	}
}