package com.example.myapplication

import android.content.Context
import android.net.wifi.WifiManager
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.myapplication.adapter.MainScreenAdapter


class MainActivity : AppCompatActivity() {
    lateinit var list : RecyclerView
    var name = arrayOf("Device","Model","Hardware","Android Version","Mac Address")


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        list = findViewById(R.id.listRecyclerView)
        list.layoutManager = LinearLayoutManager(this)
        list.adapter = MainScreenAdapter(name,getResult());

        // Example of a call to a native method
        for (element in getResult()){
            Log.i("test",element)
        }
    }



    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
//    external fun getMacAddress() : String
    private external fun getResult(): Array<String>


    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}