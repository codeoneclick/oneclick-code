package Game.level 
{
	import common.mvc.IController;
	import flash.display.DisplayObjectContainer;
	import Game.elements.TileController;
	/**
	 * ...
	 * @author ...
	 */
	public class LevelController extends IController
	{
		private var m_levelWidth:int = 64;
		private var m_levelHeight:int = 64;
		private const k_TILE_WIDTH:int = 32;
		private const k_TILE_HEIGH:int = 16;
		
		private var m_dataPath:String = "content/forest_grass_01.png";
		private var m_dataType:String = "bitmap_data";
		private var m_tileMap:Array = null;
		
		public function LevelController(_container:DisplayObjectContainer) 
		{
			super(_container, new LevelViewer(m_dataPath, m_dataType),new LevelModel());
			init();
		}
		
		private function init():void
		{
			m_tileMap = new Array;
			for (var i:int = 0; i < m_levelWidth; i++)
			{
				m_tileMap[i] = new Array;
				for (var j:int = 0; j < m_levelHeight; j++)
				{
					m_tileMap[i][j] = new TileController(m_viewer);
					(m_tileMap[i][j] as TileController).setScreenPosition(i * k_TILE_WIDTH + j * k_TILE_WIDTH / 2, j * k_TILE_HEIGH / 2);
				}
			}
		}
		
	}

}