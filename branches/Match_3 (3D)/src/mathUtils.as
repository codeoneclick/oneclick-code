package  
{
	
	/**
	 * ...
	 * @author PsyTech
	 */
	public class mathUtils 
	{
		
		public function mathUtils() 
		{
			
		}
		
		public static function matrixMulMatrix(matrixOneIn:matrix, matrixTwoIn:matrix):matrix
		{
			var matrixResult:matrix = new matrix();
			////////////////////////////////////////////////////
			matrixResult.m[0] = matrixOneIn.m[0] * matrixTwoIn.m[0];
			matrixResult.m[1] = matrixOneIn.m[1] * matrixTwoIn.m[4];
			matrixResult.m[2] = matrixOneIn.m[2] * matrixTwoIn.m[8];
			matrixResult.m[3] = matrixOneIn.m[3] * matrixTwoIn.m[12];
			////////////////////////////////////////////////////
			matrixResult.m[4] = matrixOneIn.m[4] * matrixTwoIn.m[1];
			matrixResult.m[5] = matrixOneIn.m[5] * matrixTwoIn.m[5];
			matrixResult.m[6] = matrixOneIn.m[6] * matrixTwoIn.m[9];
			matrixResult.m[7] = matrixOneIn.m[7] * matrixTwoIn.m[13];
			///////////////////////////////////////////////////
			matrixResult.m[8] = matrixOneIn.m[8] * matrixTwoIn.m[2];
			matrixResult.m[9] = matrixOneIn.m[9] * matrixTwoIn.m[6];
			matrixResult.m[10] = matrixOneIn.m[10] * matrixTwoIn.m[10];
			matrixResult.m[11] = matrixOneIn.m[11] * matrixTwoIn.m[14];
			///////////////////////////////////////////////////
			matrixResult.m[12] = matrixOneIn.m[12] * matrixTwoIn.m[3];
			matrixResult.m[13] = matrixOneIn.m[13] * matrixTwoIn.m[7];
			matrixResult.m[14] = matrixOneIn.m[14] * matrixTwoIn.m[11];
			matrixResult.m[15] = matrixOneIn.m[15] * matrixTwoIn.m[15];
			//////////////////////////////////////////////////
			return matrixResult;
		}
		
		public static function matrixMulVector(vectorIn:vector, matrixIn:matrix):vector
		{
		    var vectorResult:vector = new vector();
			vectorResult.x =matrixIn.m[0] * vectorIn.x +matrixIn.m[1] * vectorIn.y +matrixIn.m[2] * vectorIn.z +matrixIn.m[3] * vectorIn.w;
			vectorResult.y =matrixIn.m[4] * vectorIn.x +matrixIn.m[5] * vectorIn.y +matrixIn.m[6] * vectorIn.z +matrixIn.m[7] * vectorIn.w;
			vectorResult.z =matrixIn.m[8] * vectorIn.x +matrixIn.m[9] * vectorIn.y +matrixIn.m[10] * vectorIn.z +matrixIn.m[11] * vectorIn.w;
			vectorResult.w = matrixIn.m[12] * vectorIn.x +matrixIn.m[13] * vectorIn.y +matrixIn.m[14] * vectorIn.z +matrixIn.m[15] * vectorIn.w;
			return vectorResult;
		}
		
		public static function createMatrixProjection(nearPlane:Number, farPlane:Number, fov:Number,aspect:Number):matrix
		{
			var matrixProjection:matrix = new matrix();
			matrixZero(matrixProjection);
			var yScale:Number = new Number( 1 / Math.tan(fov/2) );
			var xScale:Number = new Number( yScale );
			matrixProjection.m[0] = xScale;
			matrixProjection.m[5] = yScale;
			matrixProjection.m[10] = farPlane / (nearPlane - farPlane);
			matrixProjection.m[11] = 1.0;
			matrixProjection.m[14] = -nearPlane * farPlane / (nearPlane - farPlane);
			matrixProjection.m[15] = 0.0;
			return matrixProjection;
		}
		
		public static function matrixZero(matrixIn:matrix):void
		{
			var i:int;
			for (i = 0; i < 16; i++)
				matrixIn.m[i] = 0.0;
		}
		
		public static function matrixTranslate(vectorIn:vector):matrix
		{
			var matrixTranslation:matrix = new matrix();
			mathUtils.matrixZero(matrixTranslation);
			matrixTranslation.m[0] = 1;
			matrixTranslation.m[5] = 1;
			matrixTranslation.m[10] = 1;
			matrixTranslation.m[15] = 1;
			matrixTranslation.m[3] = vectorIn.x;
			matrixTranslation.m[7] = vectorIn.y;
			matrixTranslation.m[11] = vectorIn.z;
			return matrixTranslation;
		}
		
		public static function matrixRotateX(value:Number):matrix
		{
			var matrixRotationX:matrix = new matrix();
			mathUtils.matrixZero(matrixRotationX);
			matrixRotationX.m[0] = 1;
			matrixRotationX.m[15] = 1;
			matrixRotationX.m[5] = Math.cos(value);
			matrixRotationX.m[6] = Math.sin(value);
			matrixRotationX.m[9] = -Math.sin(value);
			matrixRotationX.m[10] = Math.cos(value);
			return matrixRotationX;
		}
		
		public static function matrixRotateY(value:Number):matrix
		{
			var matrixRotationY:matrix = new matrix();
			mathUtils.matrixZero(matrixRotationY);
			matrixRotationY.m[5] = 1;
			matrixRotationY.m[15] = 1;
			matrixRotationY.m[0] = Math.cos(value);
			matrixRotationY.m[2] = -Math.sin(value);
			matrixRotationY.m[8] = Math.sin(value);
			matrixRotationY.m[10] = Math.cos(value);
			return matrixRotationY;
		}
		
		public static function matrixRotateZ(value:Number):matrix
		{
			var matrixRotationZ:matrix = new matrix();
			mathUtils.matrixZero(matrixRotationZ);
			matrixRotationZ.m[10] = 1;
			matrixRotationZ.m[15] = 1;
			matrixRotationZ.m[0] = Math.cos(value);
			matrixRotationZ.m[1] = Math.sin(value);
			matrixRotationZ.m[4] = -Math.sin(value);
			matrixRotationZ.m[5] = Math.cos(value);
			return matrixRotationZ;
		}
	}
	
}