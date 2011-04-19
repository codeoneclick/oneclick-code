package game.enviroment 
{
	import common.helper3d.Container3d;
	import common.helper3d.Sprite3d;
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
		
		private var m_tilesList:Vector.<GroundCell> = new Vector.<GroundCell>();
		private var m_wallsList:Vector.<Building> = new Vector.<Building>();
		
		private var m_mapContainer:Container3d = new Container3d();
		
		private var m_visualLayers:Dictionary = new Dictionary();
		
		private static var m_workingGroundCell:GroundCell = null;
		private static var m_workingBuildingCell:Building = null;
		
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
				for (var j:int = 0; j < k_MAP_HEIGHT; j++)
				{
					m_workingGroundCell = new GroundCell(m_visualLayers[k_MAP_LAYER], new Point(GroundCell.k_WIDTH, GroundCell.k_HEIGHT), k_TILE_RES_NAME);
					m_workingGroundCell.Parent = m_mapContainer;
					m_workingGroundCell.Rotation.x = 1.57;
					m_workingGroundCell.Position.x = (GroundCell.k_WIDTH - 1) * i - GroundCell.k_WIDTH * k_MAP_WIDTH / 2;
					m_workingGroundCell.Position.z = (GroundCell.k_HEIGHT - 1) * j - GroundCell.k_HEIGHT * k_MAP_HEIGHT / 2;
					m_tilesList.push(m_workingGroundCell);
				}
			}	
			
			for (var i:int = 0; i < k_MAP_WIDTH; i++)
			{
				for (var j:int = 0; j < k_MAP_HEIGHT; j++)
				{
					if (i % 2 > 0)
					{
						m_workingBuildingCell = new Building(m_visualLayers[K_CHARACTER_LAYER], new Point(GroundCell.k_WIDTH, GroundCell.k_HEIGHT), "pic0");
					}
					else if ( j % 2 > 0)
					{
						m_workingBuildingCell = new Building(m_visualLayers[K_CHARACTER_LAYER], new Point(GroundCell.k_WIDTH, GroundCell.k_HEIGHT), "pic1");
					}
					else
					{
						m_workingBuildingCell = new Building(m_visualLayers[K_CHARACTER_LAYER], new Point(GroundCell.k_WIDTH, GroundCell.k_HEIGHT), "pic3");
					}
					
					if ( i == 0 || j == 0 || i == (k_MAP_WIDTH - 1) || j == (k_MAP_WIDTH - 1))
						m_workingBuildingCell = new Building(m_visualLayers[K_CHARACTER_LAYER], new Point(GroundCell.k_WIDTH, GroundCell.k_HEIGHT), "pic2");
				
					m_workingBuildingCell.Parent = m_mapContainer;
					m_workingBuildingCell.Rotation.y = 0;
					m_workingBuildingCell.Position.x = GroundCell.k_WIDTH * i - GroundCell.k_WIDTH * k_MAP_WIDTH / 2;
					m_workingBuildingCell.Position.z = GroundCell.k_HEIGHT * j - GroundCell.k_HEIGHT * k_MAP_HEIGHT / 2;
					m_workingBuildingCell.Position.y = GroundCell.k_WIDTH / 2;
					
					m_wallsList.push(m_workingBuildingCell);
				}
			}	
			
			Core.stage.addEventListener(Event.ENTER_FRAME, update);
		}
		
		private function update(_event:Event):void
		{
			m_mapContainer.Position = Core.camera.Position;
			zOrder();
			m_mapContainer.Rotation.y = 0.7;//+= 0.0285;
		}
		
		private function zOrder():void
		{
			var mapLayer:Sprite = m_visualLayers[k_MAP_LAYER];
			m_tilesList.sort(spriteSorter);
			for (var i:int = 0; i < m_tilesList.length; i++)
			{
				mapLayer.setChildIndex(m_tilesList[i], i);
			}	
			
			var characterLayer:Sprite = m_visualLayers[K_CHARACTER_LAYER];
			m_wallsList.sort(spriteSorter);
			for (var i:int = 0; i < m_wallsList.length; i++)
			{
				characterLayer.setChildIndex(m_wallsList[i], i);
				m_wallsList[i].Rotation.y = -0.7;//-= 0.0285;
			}	
		}
		
		private final function spriteSorter(_value_01:Sprite3d,_value_02:Sprite3d) : Number
		{
			if (_value_01.zIndex < _value_02.zIndex)
				return -1;
			if (_value_01.zIndex > _value_02.zIndex)
				return 1;
			return 0;
		}
	}
}