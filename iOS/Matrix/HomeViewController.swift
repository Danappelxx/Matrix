//
//  HomeViewController.swift
//  Matrix
//
//  Created by Dan Appel on 11/9/18.
//  Copyright © 2018 Dan Appel. All rights reserved.
//

import UIKit
import Starscream

class HomeViewController: UIViewController {

    @IBOutlet weak var statusLabel: UILabel!

    let socket = WebSocket(url: URL(string: "ws://192.168.1.5")!)
    override func viewDidLoad() {
        super.viewDidLoad()

        socket.connect()
        statusLabel.text = "Connecting..."
        socket.onConnect = { [weak self] in
            self?.statusLabel.text = "Connected!"
        }
        socket.onDisconnect = { [weak self] _ in
            self?.statusLabel.text = "Disconnected!"
        }
    }

    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "showSnake" {
            let snakeVC = segue.destination as! SnakeViewController
            snakeVC.socket = self.socket
        }
    }
}
