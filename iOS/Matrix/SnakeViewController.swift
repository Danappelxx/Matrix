//
//  SnakeViewController.swift
//  Matrix
//
//  Created by Dan Appel on 11/9/18.
//  Copyright © 2018 Dan Appel. All rights reserved.
//

import UIKit
import Starscream

enum Direction: String {
    case left = "LEFT"
    case right = "RIGHT"
    case up = "UP"
    case down = "DOWN"
}

class SnakeViewController: UIViewController {

    var socket: WebSocket!

    override func viewDidLoad() {
        super.viewDidLoad()

        print("is connected? \(self.socket.isConnected)")
        socket.write(string: "AI_OFF")

        let up = UISwipeGestureRecognizer(target: self, action: #selector(didSwipe(swipe:)))
        let down = UISwipeGestureRecognizer(target: self, action: #selector(didSwipe(swipe:)))
        let left = UISwipeGestureRecognizer(target: self, action: #selector(didSwipe(swipe:)))
        let right = UISwipeGestureRecognizer(target: self, action: #selector(didSwipe(swipe:)))
        up.direction = .up
        down.direction = .down
        left.direction = .left
        right.direction = .right
        self.view.addGestureRecognizer(up)
        self.view.addGestureRecognizer(down)
        self.view.addGestureRecognizer(left)
        self.view.addGestureRecognizer(right)
    }

    @objc func didSwipe(swipe: UISwipeGestureRecognizer) {
        switch swipe.direction {
        case .up: send(direction: .up)
        case .down: send(direction: .down)
        case .left: send(direction: .left)
        case .right: send(direction: .right)
        default: break
        }
    }

    override func viewWillDisappear(_ animated: Bool) {
        socket.write(string: "AI_ON")
    }

    func send(direction: Direction) {
        print(direction)
        // send to websocket
        socket.write(string: direction.rawValue)
    }
}
