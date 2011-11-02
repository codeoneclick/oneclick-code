package game 
{
	import adobe.utils.CustomActions;
	import core.Global;
	import fl.controls.Button;
	import flash.display.Sprite;
	import flash.geom.Point;
	import flash.utils.ByteArray;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class SceneController 
	{	
		private static const k_DEFAULT_LAYER:String = "DEFAULT_LAYER";
		private static const k_SECTOR_INDEX:String = "SECTOR_INDEX";
		
		private var m_gameNodeContainer:Vector.<GameNode> = new Vector.<GameNode>();
		private var m_characterNode:Character = null;
		
		private var m_mapContainer:Dictionary = new Dictionary();
		
		private var m_visualLayers:Dictionary = new Dictionary();	
		
		private var m_background:Background = null;
		
		public function SceneController() 
		{
			m_background = new Background(Global.backContainer);
			m_background.load("back_03");
		}
		
		public function initDefault():void
		{
			m_visualLayers[k_DEFAULT_LAYER] = new Sprite();
			Global.inGameContainer.addChild(m_visualLayers[k_DEFAULT_LAYER]);
			Global.editorController.addSector(new Point(0, 0), "sector_01", Sector.k_SECTOR_LAYER);
		}
		
		public function get visualLayers():Sprite
		{
			return m_visualLayers[k_DEFAULT_LAYER] as Sprite;
		}
		
		public function addSector(_position:Point, _name:String, _layer:int):Boolean
		{
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] != null && m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] != null )
			{
				changeSector(_position, _name, _layer);
				return false;
			}
			
			
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] == null)
			{
				 m_mapContainer[k_SECTOR_INDEX + _position.x] = new Dictionary();
			}
			
			m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] = new Sector(m_visualLayers[k_DEFAULT_LAYER]);
			m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].Load(_name, _layer);
			calculatePosition(_position);
			m_gameNodeContainer.push(m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y]);
			m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].index = new Point(_position.x, _position.y);
			
			return true;
		}
		
		public function addSubSectors(_position:Point):void
		{
			
			Global.sceneController.addSubSector( new Point(_position.x, _position.y - 2) );
			Global.sceneController.addSubSector( new Point(_position.x, _position.y + 2) );
				
			Global.sceneController.addSubSector( new Point(_position.x - 1, _position.y) );
			Global.sceneController.addSubSector( new Point(_position.x + 1, _position.y) );
				
			Global.sceneController.addSubSector( new Point(_position.x, _position.y - 1) );
			Global.sceneController.addSubSector( new Point(_position.x, _position.y + 1) );
			
			if (Math.abs(_position.y) % 2 > 0)
			{	
				Global.sceneController.addSubSector( new Point(_position.x - 1, _position.y - 1) );
				Global.sceneController.addSubSector( new Point(_position.x - 1, _position.y + 1) );
			}
			else
			{
				Global.sceneController.addSubSector( new Point(_position.x + 1, _position.y - 1) );
				Global.sceneController.addSubSector( new Point(_position.x + 1, _position.y + 1) );
			}
		}
		
		private function addSubSector(_position:Point):void
		{
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] == null )
			{
				m_mapContainer[k_SECTOR_INDEX + _position.x] = new Dictionary();
			}
						
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] == null)
			{
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] = new Sector(m_visualLayers[k_DEFAULT_LAYER]);
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].Load(Sector.k_SECTOR_DEFAULT_NAME, Sector.k_SECTOR_LAYER);
				calculatePosition(new Point(_position.x , _position.y));
				m_gameNodeContainer.push(m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y]);
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].index = new Point(_position.x,_position.y);
			}
		}
		
		public function removeSector(_position:Point, _layer:int):void
		{
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] != null && m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] != null )
			{
				if (_layer == Sector.k_SECTOR_LAYER)
				{
					changeSector(_position, Sector.k_SECTOR_DEFAULT_NAME, _layer);
				}
				else if (_layer == Sector.k_DECORATION_LAYER)
				{
					changeSector(_position, Sector.k_DECORATION_DEFAULT_NAME, _layer);
				}
			}
		}
		
		public function removeSubSectors(_position:Point):void
		{
			Global.sceneController.removeSubSector( new Point(_position.x, _position.y - 2) );
			Global.sceneController.removeSubSector( new Point(_position.x, _position.y + 2) );
				
			Global.sceneController.removeSubSector( new Point(_position.x - 1, _position.y) );
			Global.sceneController.removeSubSector( new Point(_position.x + 1, _position.y) );
				
			Global.sceneController.removeSubSector( new Point(_position.x, _position.y - 1) );
			Global.sceneController.removeSubSector( new Point(_position.x, _position.y + 1) );
			
			if (Math.abs(_position.y) % 2 > 0)
			{	
				Global.sceneController.removeSubSector( new Point(_position.x - 1, _position.y - 1) );
				Global.sceneController.removeSubSector( new Point(_position.x - 1, _position.y + 1) );
			}
			else
			{
				Global.sceneController.removeSubSector( new Point(_position.x + 1, _position.y - 1) );
				Global.sceneController.removeSubSector( new Point(_position.x + 1, _position.y + 1) );
			}
		}
		
		public function removeSubSector(_position:Point):void
		{
			if (m_mapContainer[k_SECTOR_INDEX + _position.x] != null && 
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] != null)
			{
				return;
			}
			
			if (m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].sectorName == Sector.k_SECTOR_DEFAULT_NAME &&
				!checkSubSectors(_position))
			{
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].unLoad(Sector.k_SECTOR_LAYER);
				m_gameNodeContainer.splice(m_gameNodeContainer.indexOf(m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y]), 1);
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] = null;
			}
		}
		
		public function checkSubSectors(_position:Point):Boolean
		{
			
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] != null && 
				 m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + (_position.y - 2)] != null && 
				 m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + (_position.y - 2)].sectorName != Sector.k_SECTOR_DEFAULT_NAME)
				 return true;
			
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] != null && 
				 m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + (_position.y + 2)] != null && 
				 m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + (_position.y + 2)].sectorName != Sector.k_SECTOR_DEFAULT_NAME)
				 return true;
				
			if ( m_mapContainer[k_SECTOR_INDEX + (_position.x - 1)] != null && 
				 m_mapContainer[k_SECTOR_INDEX + (_position.x - 1)][k_SECTOR_INDEX + _position.y] != null && 
				 m_mapContainer[k_SECTOR_INDEX + (_position.x - 1)][k_SECTOR_INDEX + _position.y].sectorName != Sector.k_SECTOR_DEFAULT_NAME)
				 return true;
				
			if ( m_mapContainer[k_SECTOR_INDEX + (_position.x + 1)] != null && 
				 m_mapContainer[k_SECTOR_INDEX + (_position.x + 1)][k_SECTOR_INDEX + _position.y] != null && 
				 m_mapContainer[k_SECTOR_INDEX + (_position.x + 1)][k_SECTOR_INDEX + _position.y].sectorName != Sector.k_SECTOR_DEFAULT_NAME)
				 return true;
				
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] != null && 
				 m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + (_position.y - 1)] != null && 
				 m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + (_position.y - 1)].sectorName != Sector.k_SECTOR_DEFAULT_NAME)
				 return true;
				
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] != null && 
				 m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + (_position.y + 1)] != null && 
				 m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + (_position.y + 1)].sectorName != Sector.k_SECTOR_DEFAULT_NAME)
				 return true;
	
			
			if (Math.abs(_position.y) % 2 > 0)
			{	
				
				if ( m_mapContainer[k_SECTOR_INDEX + (_position.x - 1)] != null && 
					 m_mapContainer[k_SECTOR_INDEX + (_position.x - 1)][k_SECTOR_INDEX + (_position.y - 1)] != null && 
					 m_mapContainer[k_SECTOR_INDEX + (_position.x - 1)][k_SECTOR_INDEX + (_position.y - 1)].sectorName != Sector.k_SECTOR_DEFAULT_NAME)
					 return true;
					 
				if ( m_mapContainer[k_SECTOR_INDEX + (_position.x - 1)] != null && 
					 m_mapContainer[k_SECTOR_INDEX + (_position.x - 1)][k_SECTOR_INDEX + (_position.y + 1)] != null && 
					 m_mapContainer[k_SECTOR_INDEX + (_position.x - 1)][k_SECTOR_INDEX + (_position.y + 1)].sectorName != Sector.k_SECTOR_DEFAULT_NAME)
					 return true;
			}
			else
			{
				if ( m_mapContainer[k_SECTOR_INDEX + (_position.x + 1)] != null && 
					 m_mapContainer[k_SECTOR_INDEX + (_position.x + 1)][k_SECTOR_INDEX + (_position.y - 1)] != null && 
					 m_mapContainer[k_SECTOR_INDEX + (_position.x + 1)][k_SECTOR_INDEX + (_position.y - 1)].sectorName != Sector.k_SECTOR_DEFAULT_NAME)
					 return true;
					 
				if ( m_mapContainer[k_SECTOR_INDEX + (_position.x + 1)] != null && 
					 m_mapContainer[k_SECTOR_INDEX + (_position.x + 1)][k_SECTOR_INDEX + (_position.y + 1)] != null && 
					 m_mapContainer[k_SECTOR_INDEX + (_position.x + 1)][k_SECTOR_INDEX + (_position.y + 1)].sectorName != Sector.k_SECTOR_DEFAULT_NAME)
					 return true;
			}
			
			 return false;
		}
		
		public function zOrder():void
		{
			m_gameNodeContainer.sort(GameNode.sorter);
			for (var i:int = 0; i < m_gameNodeContainer.length; i++)
			{
				m_visualLayers[k_DEFAULT_LAYER].setChildIndex(m_gameNodeContainer[i], i);
			}	
		}	
		
		public function changeSector(_position:Point, _name:String, _layer:int):Boolean
		{
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] == null )
			{
				return false;
			}
			
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] == null )
			{
				return false;
			}
			
			m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].Load(_name, _layer);
			
			return true;
		}
		
		private function calculatePosition(_position:Point):void
		{
			if ( Math.abs(_position.y) % 2 > 0 )
			{
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].position.x = _position.x * Sector.k_SECTOR_WIDTH;
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].position.y = _position.y * Sector.k_SECTOR_HEIGHT / 2;
			}
			else
			{
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].position.x = _position.x * Sector.k_SECTOR_WIDTH + Sector.k_SECTOR_WIDTH / 2;
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].position.y = _position.y * Sector.k_SECTOR_HEIGHT / 2;
			}
		}
		
		public function SaveMapData():ByteArray
		{
			var mapData:ByteArray = new ByteArray();
			var sector:Sector = null;
			
			mapData.writeInt(m_gameNodeContainer.length);
			
			for ( var i:int = 0; i < m_gameNodeContainer.length; i++)
			{
				sector = m_gameNodeContainer[i] as Sector;
				mapData.writeInt(sector.index.x);
				mapData.writeInt(sector.index.y);
				mapData.writeUTF(sector.sector);
				mapData.writeUTF(sector.decoration);
  			}
			
			return mapData;
		}
		
		public function LoadMapData(_data:ByteArray):void
		{
			var sectorCount:int = _data.readInt();
			
			for (var i:int = 0; i < sectorCount; i++ )
			{
				var mapNode:MapStruct = new MapStruct();
				mapNode.m_index.x = _data.readInt();
				mapNode.m_index.y = _data.readInt();
				
				mapNode.m_sector = _data.readUTF();
				mapNode.m_decoration = _data.readUTF();
				
				if ( mapNode.m_sector != Sector.k_SECTOR_DEFAULT_NAME )
				{
					Global.editorController.addSector(mapNode.m_index, mapNode.m_sector, Sector.k_SECTOR_LAYER);
				}
				
				if ( mapNode.m_decoration != Sector.k_DECORATION_DEFAULT_NAME )
				{
					Global.editorController.addSector(mapNode.m_index, mapNode.m_decoration, Sector.k_DECORATION_LAYER);
				}
			}
			
			Global.camera.goToCenter();
		}
		
		public function ClearMapData():void
		{
			for ( var i:int = 0; i < m_gameNodeContainer.length; i++)
			{
				m_visualLayers[k_DEFAULT_LAYER].removeChild(m_gameNodeContainer[i]);
			}
			
			m_gameNodeContainer = new Vector.<GameNode>();
			m_mapContainer = new Dictionary();
		}
	
	}
}
import flash.geom.Point;

class MapStruct
{
	public var m_index:Point = new Point();
	public var m_sector:String = "";
	public var m_decoration:String = "";
	
	public function MapStruct()
	{
		
	}
}