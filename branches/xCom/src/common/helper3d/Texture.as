package common.helper3d 
{
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.geom.Matrix;
	import flash.geom.Point;
	
	/**
	 * ...
	 * @author ...
	 */
	public class Texture 
	{
		
		private var m_source:Sprite = null;		
		private var m_bitmapData:BitmapData = null;
		private var m_size:Point = new Point();
	
		private var m_pointList:Array = null;			
		private var m_triangleList:Array = null;	
	
		public function Texture(_source:Sprite, _size:Point)
		{
			m_source = _source;
			m_size = _size;
			init();
		}
	
		private function init():void
		{
			m_pointList = new Array();
			m_triangleList = new Array();
			
			for (var i:int = 0 ; i < 2 ; i++ )
			{
				for (var j:int = 0 ; j < 2 ; j++ )
				{
					m_pointList.push( { x: ( i * m_size.x ), y: ( j * m_size.y ), sx: ( i * m_size.x ), sy: ( j * m_size.y ) } );
				}
			}

			m_triangleList.push([ m_pointList[ 0 ] , m_pointList[ 1 ] , m_pointList[ 2 ] ] );
			m_triangleList.push([ m_pointList[ 3 ] , m_pointList[ 2 ] , m_pointList[ 1 ] ] );
			rasterize();
		}	
		
		public function set bitmapData(_bitmapData:BitmapData):void
		{
			m_bitmapData = _bitmapData;
		}	
 
		public function transform(_sspLeftBottom:Point, _sspRightBottom:Point, _sspRightTop:Point, _sspLeftTop:Point):void
		{
			var dxLTLB:Number = _sspLeftTop.x - _sspLeftBottom.x;
			var dyLTLB:Number = _sspLeftTop.y - _sspLeftBottom.y;
			var dxRTRB:Number = _sspRightTop.x - _sspRightBottom.x;
			var dyRTRB:Number = _sspRightTop.y - _sspRightBottom.y;
			var index:Number = m_pointList.length;
			while( --index > -1 )
			{
				var point:Object = m_pointList[index];
				var gx:Number = ( point.x) / m_size.x;
				var gy:Number = ( point.y) / m_size.y;
				var bx:Number = _sspLeftBottom.x + gy * ( dxLTLB );
				var by:Number = _sspLeftBottom.y + gy * ( dyLTLB );
	 
				point.sx = bx + gx * ( ( _sspRightBottom.x + gy * ( dxRTRB ) ) - bx );
				point.sy = by + gx * ( ( _sspRightBottom.y + gy * ( dyRTRB ) ) - by );
			}
		}
 
		public function rasterize():void
		{
			if (m_bitmapData == null) 
				return;
				
			m_source.graphics.clear();
			
			var point_0:Object = null;
			var point_1:Object = null;
			var point_2:Object = null;
			var triangle:Array = null;
			var matrixS:Matrix = new Matrix();
			var matrixT:Matrix = new Matrix();
			
			var index:Number = 2;
			while( --index > -1 )
			{
				triangle = m_triangleList[ index ];
				point_0 = triangle[0];
				point_1 = triangle[1];
				point_2 = triangle[2];
	 
				matrixT.tx = point_0.x;
				matrixT.ty = point_0.y;
			
				matrixT.a = ( point_1.x - point_0.x );
				matrixT.b = ( point_1.y - point_0.y );
				matrixT.c = ( point_2.x - point_0.x );
				matrixT.d = ( point_2.y - point_0.y );
			
				matrixS.a = ( point_1.sx - point_0.sx );
				matrixS.b = ( point_1.sy - point_0.sy );
				matrixS.c = ( point_2.sx - point_0.sx );
				matrixS.d = ( point_2.sy - point_0.sy );
			
				matrixS.tx = point_0.sx;
				matrixS.ty = point_0.sy;
			
				matrixT.invert();
				matrixT.concat( matrixS );
				m_source.graphics.beginBitmapFill( m_bitmapData, matrixT, false, false );
				m_source.graphics.moveTo( point_0.x, point_0.y );
				m_source.graphics.lineTo( point_1.x, point_0.y );
				m_source.graphics.lineTo( point_2.x, point_2.y );
				m_source.graphics.endFill();
			}
		}
 
		
	}

}