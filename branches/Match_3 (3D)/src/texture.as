package  
{

import flash.geom.Matrix;
import flash.display.BitmapData;
import flash.display.MovieClip;
 
public class texture
{
	private var sourceMovieClip         :MovieClip;			// Исходный мувиклип на который будем лепить текстуру.
	public  var sourceImage				:BitmapData;		// Исходная картинка которую будем лепить на мувиклип.
	
	private var width					:Number;			// Ширина.
	private var height					:Number;			// Высота.

	private var matrixScale				:Matrix;			// Матрица масштабирования.
	private	var matrixTranslate			:Matrix;			// Матрица для переноса точек.
	
	private var pointList				:Array;				// Список точек.
	private var triangleList			:Array;				// Список треугольников.
	
	
	public function texture(sourceMovieClip:MovieClip)
	{
		this.sourceMovieClip = sourceMovieClip;
		width = 256;
		height = 256;
		init();
		
	}
	
	public function setSourceImage(sourceImage:BitmapData):void
	{
		this.sourceImage = sourceImage;
	}
 
 
	private function init():void
	{
		pointList = new Array();
		triangleList = new Array();
	
		var i:int;
		var j:int;
		for ( i = 0 ; i < 2 ; i++ )
		{
			for ( j = 0 ; j < 2 ; j++ )
			{
				pointList.push( { x: (i * width), y: (j * height), sx: (i * width), sy: (j * height) } );
			}
		}

		triangleList.push([ pointList[ 0 ] , pointList[ 1 ] , pointList[ 2 ] ] );
		triangleList.push([ pointList[ 3 ] , pointList[ 2 ] , pointList[ 1 ] ] );
 
		render();
	}
 
	public function setTransform( x0:Number , y0:Number , x1:Number , y1:Number , x2:Number , y2:Number , x3:Number , y3:Number ):void
	{
		var w:Number = width;
		var h:Number = height;
		var dx30:Number = x3 - x0;
		var dy30:Number = y3 - y0;
		var dx21:Number = x2 - x1;
		var dy21:Number = y2 - y1;
		var l:Number = pointList.length;
		while( --l > -1 )
		{
			var point:Object = pointList[ l ];
			var gx:Number = ( point.x) / w;
			var gy:Number = ( point.y) / h;
			var bx:Number = x0 + gy * ( dx30 );
			var by:Number = y0 + gy * ( dy30 );
 
			point.sx = bx + gx * ( ( x1 + gy * ( dx21 ) ) - bx );
			point.sy = by + gx * ( ( y1 + gy * ( dy21 ) ) - by );
		}
	}
 
	public function render():void
	{
		if (this.sourceImage == null) return;
		
		var t: Number;
		var vertices: Array;
		var p0:Object;
		var p1:Object;
		var p2:Object;
		var a:Array;
		sourceMovieClip.graphics.clear();
		matrixScale = new Matrix();
		matrixTranslate = new Matrix();
		
		var l:Number = 2;
		while( --l > -1 )
		{
			a = triangleList[ l ];
			p0 = a[0];
			p1 = a[1];
			p2 = a[2];
			var x0: Number = p0.sx;
			var y0: Number = p0.sy;
			var x1: Number = p1.sx;
			var y1: Number = p1.sy;
			var x2: Number = p2.sx;
			var y2: Number = p2.sy;
				
			var u0: Number = p0.x;
			var v0: Number = p0.y;
			var u1: Number = p1.x;
			var v1: Number = p1.y;
			var u2: Number = p2.x;
			var v2: Number = p2.y;
 
			matrixTranslate.tx = u0;
			matrixTranslate.ty = v0;
		
			matrixTranslate.a = ( u1 - u0 );
			matrixTranslate.b = ( v1 - v0 );
			matrixTranslate.c = ( u2 - u0 );
			matrixTranslate.d = ( v2 - v0 );
		
			matrixScale.a = ( x1 - x0 );
			matrixScale.b = ( y1 - y0 );
			matrixScale.c = ( x2 - x0 );
			matrixScale.d = ( y2 - y0 );
		
			matrixScale.tx = x0;
			matrixScale.ty = y0;
		
			matrixTranslate.invert();
			matrixTranslate.concat( matrixScale );
			sourceMovieClip.graphics.beginBitmapFill( sourceImage, matrixTranslate, false, false );
			sourceMovieClip.graphics.moveTo( x0, y0 );
			sourceMovieClip.graphics.lineTo( x1, y1 );
			sourceMovieClip.graphics.lineTo( x2, y2 );
			sourceMovieClip.graphics.endFill();
		
		}
	}
 
}
}