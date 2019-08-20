import { DroneState } from '../drone-data/drone/drone-state.enum';
export class FlightSession {
  private detectionImages: string [] = [];
  private sessionName: string;
  public active: boolean;
  constructor() {
    console.log('Arming drone!');
    this.active = false;
    this.sessionName = 'mock_name';
  }
  setSessionName(sessionName) {
    this.sessionName = sessionName;
  }
  addImage(image) {
    this.detectionImages.unshift('data:image/jpg;base64,' + image);
  }
  getImage(index) {
    return this.detectionImages[index];
  }
  getImages() {
    return this.detectionImages;
  }
  getSessionName() {
    return this.sessionName;
  }
  isActive(): boolean {
    return this.active;
  }
  getFirstImage() {
    if (this.detectionImages[0] !== undefined) {
      return this.detectionImages[this.detectionImages.length - 1];
    } else {
      return './assets/mockshots/predictionRhino.jpg';
    }
  }
}