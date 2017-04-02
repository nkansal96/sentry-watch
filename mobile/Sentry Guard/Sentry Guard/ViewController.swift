//
//  ViewController.swift
//  Sentry Guard
//
//  Created by Nikhil Kansal on 4/1/17.
//  Copyright © 2017 Nikhil Kansal. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITextFieldDelegate {
    var settingsURL: String = "http://sentrywatch.herokuapp.com/api/mobile/configure";
    
    @IBOutlet weak var emergencyContact1: UITextField!
    @IBOutlet weak var emergencyContact2: UITextField!
    @IBOutlet weak var name: UITextField!
    @IBOutlet weak var alertEmergencyServices: UISwitch!
    @IBOutlet weak var enableStruggleDetection: UISwitch!
    @IBOutlet weak var enablePanicButton: UISwitch!
    @IBOutlet weak var enableSound: UISwitch!
    @IBOutlet weak var enableLEDs: UISwitch!

    @IBOutlet weak var saveButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        saveButton.addTarget(self, action: #selector(ViewController.sendSettings), for: .touchUpInside)
        let doneToolbar: UIToolbar = UIToolbar(frame: CGRect(x: 0, y: 0, width: 320, height: 50))
        doneToolbar.barStyle = UIBarStyle.blackTranslucent
        
        let flexSpace = UIBarButtonItem(barButtonSystemItem: UIBarButtonSystemItem.flexibleSpace, target: nil, action: nil)
        let done: UIBarButtonItem = UIBarButtonItem(title: "Done", style: UIBarButtonItemStyle.done, target: self, action: #selector(ViewController.done))
        
        let items = NSMutableArray()
        items.add(flexSpace)
        items.add(done)
        
        doneToolbar.items = items as? [UIBarButtonItem]
        doneToolbar.sizeToFit()
        
        self.emergencyContact1.inputAccessoryView = doneToolbar
        self.emergencyContact2.inputAccessoryView = doneToolbar
        self.name.inputAccessoryView = doneToolbar
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func done() {
        name.resignFirstResponder()
        emergencyContact1.resignFirstResponder()
        emergencyContact2.resignFirstResponder()
    }
    
    func sendSettings() {
        var request = URLRequest(url: URL(string: settingsURL)!)
        request.httpMethod = "POST"
        let postString = "name=\(name.text ?? "")&emergencyContact1=\(emergencyContact1.text ?? "")&emergencyContact2=\(emergencyContact2.text ?? "")&alertEmergencyServices=\(alertEmergencyServices.isOn)&enableStruggleDetection=\(enableStruggleDetection.isOn)&enablePanicButton=\(enablePanicButton.isOn)&enableLEDs=\(enableLEDs.isOn)"
        request.httpBody = postString.data(using: .utf8)
        let task = URLSession.shared.dataTask(with: request) { data, response, error in
            guard let data = data, error == nil else { // check for fundamental networking error
                print("error=\(error)")
                return
            }
            
            if let httpStatus = response as? HTTPURLResponse, httpStatus.statusCode != 200 {           // check for http errors
                print("statusCode should be 200, but is \(httpStatus.statusCode)")
                print("response = \(response)")
            }
            
            let responseString = String(data: data, encoding: .utf8)
            print("responseString = \(responseString)")
        }
        
        task.resume()
    }
}

