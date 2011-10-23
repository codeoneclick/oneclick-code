package game 
{
	import game.core.Core;
	import game.enviroment.Level;
	/**
	 * ...
	 * @author ...
	 */
	public class Game 
	{
		private var m_level:Level = null;
		
		public function Game() 
		{
			init();
		}
		
		private function init():void
		{
			m_level = new Level();
		}
	}
}