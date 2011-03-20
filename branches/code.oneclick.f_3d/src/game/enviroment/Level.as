package game.enviroment 
{
	import common.helper3d.Container3d;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.geom.Point;
	import flash.utils.Dictionary;
	import game.core.Core;
	import game.enviroment.Building;
	import game.enviroment.GroundCell;
	/**
	 * ...
	 * @author ...
	 */
	public class Level 
	{
		public static const k_MAP_WIDTH:int  = 16;
		public static const k_MAP_HEIGHT:int = 16;
		public static const k_MAP_LAYER:String = "MAP_LAYER";
		public static const K_CHARACTER_LAYER:String = "CHARACTER_LAYER";
		private const k_TILE_RES_NAME:String = "Tile";
		
		private var m_tiles:Array = new Array();
		private var m_tilesList:Array = new Array();
		
		private var m_walls:Array = new Array();
		private var m_wallsList:Array = new Array();
		
		private var m_mapContainer:Container3d = new Container3d();
		
		private var m_visualLayers:Dictionary = new Dictionary();
		
		public function Level() 
		{
			init();
		}
		
		private function init():void
		{
			m_visualLayers[k_MAP_LAYER] = new Sprite();
			m_visualLayers[K_CHARACTER_LAYER] = new Sprite();
			
			Core.displayContainer.addChild(m_visualLayers[k_MAP_LAYER]);
			Core.displayContainer.addChild(m_visualLayers[K_CHARACTER_LAYER]);
			
			for (var i:int = 0; i < k_MAP_WIDTH; i++)
			{
				m_tiles[i] = new Array();
				for (var j:int = 0; j < k_MAP_HEIGHT; j++)
				{
					m_tiles[i][j] = new GroundCell(m_visualLayers[k_MAP_LAYER], new Point(GroundCell.k_WIDTH, GroundCell.k_HEIGHT), k_TILE_RES_NAME);
					m_tiles[i][j].Parent = m_mapContainer;
					m_tiles[i][j].Rotation.x = 1.57;
					m_tiles[i][j].Position.x = (GroundCell.k_WIDTH - 1) * i - GroundCell.k_WIDTH * k_MAP_WIDTH / 2;
					m_tiles[i][j].Position.z = (GroundCell.k_HEIGHT - 1) * j - GroundCell.k_HEIGHT * k_MAP_HEIGHT / 2;
					m_tilesList.push(m_tiles[i][j]);
				}
			}	
			
			for (var i:int = 0; i < k_MAP_WIDTH / 2; i++)
			{
				m_walls[i] = new Array();
				for (var j:int = 0; j < k_MAP_HEIGHT / 2; j++)
				{
					m_walls[i][j] = new Building(m_visualLayers[K_CHARACTER_LAYER], new Point(GroundCell.k_WIDTH, GroundCell.k_HEIGHT), "pic0");
					m_walls[i][j].Parent = m_mapContainer;
					m_walls[i][j].Rotation.y = 0;
					m_walls[i][j].Position.x = GroundCell.k_WIDTH * i - GroundCell.k_WIDTH * k_MAP_WIDTH / 2;
					m_walls[i][j].Position.z = GroundCell.k_HEIGHT * j - GroundCell.k_HEIGHT * k_MAP_HEIGHT / 2;
					m_walls[i][j].Position.y = GroundCell.k_WIDTH / 2;
					
					/*m_walls[i][j] = new Tile(m_visualLayers[K_CHARACTER_LAYER], new Point(Tile.k_TILE_WIDTH, Tile.k_TILE_HEIGHT), k_TILE_RES_NAME, new Point(i, j));
					m_walls[i][j].Parent = m_mapContainer;
					m_walls[i][j].Rotation.y = 0;
					m_walls[i][j].Position.x = Tile.k_TILE_WIDTH * i - Tile.k_TILE_WIDTH * k_MAP_WIDTH / 2 + Tile.k_TILE_WIDTH / 2;
					m_walls[i][j].Position.z = Tile.k_TILE_HEIGHT * j - Tile.k_TILE_HEIGHT * k_MAP_HEIGHT / 2;
					m_walls[i][j].Position.y = Tile.k_TILE_WIDTH / 2;*/
					
					m_wallsList.push(m_walls[i][j]);
				}
			}	
			
			Core.stage.addEventListener(Event.ENTER_FRAME, update);
		}
		
		private function update(_event:Event):void
		{
			m_mapContainer.Position.x = Core.camera.Position.x;
			m_mapContainer.Position.z = Core.camera.Position.z;
			m_mapContainer.Position.y = Core.camera.Position.y;
			zOrder();
			m_mapContainer.Rotation.y += 0.0285;
		}
		
		private function zOrder():void
		{
			var mapLayer:Sprite = m_visualLayers[k_MAP_LAYER];
			m_tilesList.sortOn("zIndex", Array.NUMERIC);
			for (var i:int = 0; i < m_tilesList.length; i++)
			{
				mapLayer.setChildIndex(m_tilesList[i], i);
			}	
			
			var characterLayer:Sprite = m_visualLayers[K_CHARACTER_LAYER];
			m_wallsList.sortOn("zIndex", Array.NUMERIC);
			for (var i:int = 0; i < m_wallsList.length; i++)
			{
				characterLayer.setChildIndex(m_wallsList[i], i);
				m_wallsList[i].Rotation.y -= 0.0285;
			}	
		}
	}
}